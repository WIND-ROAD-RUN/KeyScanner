#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "ImageProcessorModule.hpp"

#include <qfuture.h>
#include <qtconcurrentrun.h>
#include <atomic>
#include "GlobalStruct.hpp"
#include "Utilty.hpp"
#include <QPainter>
#include <QPen>
#include <cmath>
#include <algorithm>
#include "KeyScanner.h"
#include "rqw_ImagePainter.h"

namespace {
	// 在给定最小间隔内只放行一次调用：成功返回 true，其他并发/过快的调用返回 false
	inline bool AllowOncePer(std::atomic<long long>& lastNs, std::chrono::nanoseconds minInterval)
	{
		using clock = std::chrono::steady_clock;
		const auto nowNs = std::chrono::duration_cast<std::chrono::nanoseconds>(
			clock::now().time_since_epoch()).count();

		auto prev = lastNs.load(std::memory_order_relaxed);
		if (nowNs - prev < minInterval.count())
			return false; // 距上次放行未到间隔，拒绝

		// 只有一个线程能成功更新 lastNs，其他并发线程会失败并返回 false
		return lastNs.compare_exchange_strong(prev, nowNs, std::memory_order_relaxed);
	}
} // namespace


ImageProcessor::ImageProcessor(QQueue<MatInfo>& queue, QMutex& mutex, QWaitCondition& condition, int workIndex, QObject* parent)
	: QThread(parent), _queue(queue), _mutex(mutex), _condition(condition), _workIndex(workIndex)
{

}

KeyLinePixelCountResult countKeyLinePixels(
	const rw::DetectionRectangleInfo& blade,
	const rw::DetectionRectangleInfo& teeth,
	int lineY,
	const cv::Mat& mat
) {
	KeyLinePixelCountResult result;

	if (!blade.segMaskValid || !teeth.segMaskValid) return result;
	const cv::Mat& bladeMask = blade.mask_roi;
	const cv::Mat& teethMask = teeth.mask_roi;

	int totalCount{ 0 };
	int bladeTotalCount{ 0 };
	int teethTotalCount{ 0 };

	int bladeTrueSegments = 0;
	std::vector<int> bladeSegmentLengths;
	int segmentStart = -1;
	bool lastInBlade = false;
	int currentSegmentLength = 0;
	std::vector<std::pair<int, int>> bladeSegments;

	std::pair<int, int> leftEmptyRange{ 0,0 };
	std::pair<int, int> RightEmptyRange{ 0,0 };
	std::pair<int, int> keyRange{ 0,0 };
	std::pair<int, int> leftBladeRange{ 0,0 };
	std::pair<int, int> rightBladeRange{ 0,0 };
	std::pair<int, int> middleTeethRange{ 0,0 };


	int y = lineY - blade.roi.y;

	if (y < 0)
	{
		return result;
	}

	if (y <= blade.roi.height)
	{
		for (int x = 0; y>=0&&x < bladeMask.cols; ++x) {
			bool inBlade = bladeMask.at<float>(y, x) > 0;
			if (inBlade) {
				totalCount++;
				bladeTotalCount++;
				currentSegmentLength++;
			}
			if (inBlade && !lastInBlade) {
				bladeTrueSegments++;
				currentSegmentLength = 1;
				segmentStart = x; // 记录段起点
			}
			if (!inBlade && lastInBlade) {
				bladeSegmentLengths.push_back(currentSegmentLength);
				bladeSegments.push_back({ segmentStart, x - 1 }); // 记录段[left, right]
				currentSegmentLength = 0;
				segmentStart = -1;
			}
			lastInBlade = inBlade;
		}
		// 补最后一段
		if (lastInBlade && currentSegmentLength > 0) {
			bladeSegmentLengths.push_back(currentSegmentLength);
			bladeSegments.push_back({ segmentStart, bladeMask.cols - 1 });
		}

		if (!bladeSegments.empty())
		{
			leftEmptyRange.second = blade.roi.x + bladeSegments.front().first;
			RightEmptyRange.first = blade.roi.x + bladeSegments.back().second;
			RightEmptyRange.second = mat.cols;
			keyRange.first = leftEmptyRange.second;
			keyRange.second = RightEmptyRange.first;
			result.keyRange = keyRange;
			result.leftEmptyRange = leftEmptyRange;
			result.RightEmptyRange = RightEmptyRange;
		}
	}

	y = lineY - teeth.roi.y;
	std::vector<std::pair<int, int>> teethSegments;
	int teethSegmentStart = -1;
	bool lastInTeeth = false;
	int currentTeethSegmentLength = 0;

	if (y <= teeth.roi.height)
	{
		for (int x = 0;y >= 0&&x < teethMask.cols; ++x)
		{
			bool inTeeth = teethMask.at<float>(y, x) > 0;

			if (inTeeth) {
				totalCount++;
				teethTotalCount++;
				currentTeethSegmentLength++;
			}
			if (inTeeth && !lastInTeeth) {
				teethSegmentStart = x; // 新段起点
				currentTeethSegmentLength = 1;
			}
			if (!inTeeth && lastInTeeth) {
				teethSegments.push_back({ teethSegmentStart, x - 1 }); // 记录段[left, right]
				currentTeethSegmentLength = 0;
				teethSegmentStart = -1;
			}
			lastInTeeth = inTeeth;
		}
		// 补最后一段
		if (lastInTeeth && currentTeethSegmentLength > 0) {
			teethSegments.push_back({ teethSegmentStart, teethMask.cols - 1 });
		}

		if (teethSegments.size()==1)
		{
			middleTeethRange.first = teeth.roi.x + teethSegments.front().first;
			middleTeethRange.second = teeth.roi.x + teethSegments.front().second;
			result.middleTeethRange = middleTeethRange;
		}
	}



	result.totalCount = totalCount;
	result.bladeTotalCount = bladeTotalCount;
	result.middleTeethCount = teethTotalCount;

	if (bladeSegmentLengths.size() == 2)
	{
		result.leftBladeCount = bladeSegmentLengths[0];
		result.rightBladeCount = bladeSegmentLengths[1];
		leftBladeRange.first = blade.roi.x + bladeSegments[0].first;
		leftBladeRange.second = blade.roi.x + bladeSegments[0].second;
		rightBladeRange.first = blade.roi.x + bladeSegments[1].first;
		rightBladeRange.second = blade.roi.x + bladeSegments[1].second;
		result.leftBladeRange = leftBladeRange;
		result.rightBladeRange = rightBladeRange;
		
	}
	else if (bladeSegmentLengths.size() == 1)
	{
		leftBladeRange.first = blade.roi.x + bladeSegments[0].first;
		leftBladeRange.second = blade.roi.x + bladeSegments[0].second;
		result.leftBladeRange = leftBladeRange;
		rightBladeRange.first = leftBladeRange.first;
		rightBladeRange.second = leftBladeRange.second;
		result.rightBladeRange = rightBladeRange;
	}
	else if (bladeSegmentLengths.size() == 0)
	{
		leftEmptyRange.first = 0;
		leftEmptyRange.second = middleTeethRange.first;
		RightEmptyRange.first = middleTeethRange.second;
		RightEmptyRange.second = mat.cols;
		result.leftEmptyRange = leftEmptyRange;
		result.RightEmptyRange = RightEmptyRange;

	}
	else
	{
		result.leftBladeCount = 0;
		result.rightBladeCount = 0;
	}

	return result;
}

void ImageProcessor::run()
{
	while (!QThread::currentThread()->isInterruptionRequested()) {
		MatInfo frame;
		{
			QMutexLocker locker(&_mutex);
			if (_queue.isEmpty()) {
				_condition.wait(&_mutex);
				if (QThread::currentThread()->isInterruptionRequested()) {
					break;
				}
			}
			if (!_queue.isEmpty()) {
				frame = _queue.dequeue();
			}
			else {
				continue; // 如果队列仍为空，跳过本次循环
			}
		}

		// 检查 frame 是否有效
		if (frame.image.empty()) {
			continue; // 跳过空帧
		}

		auto& globalData = GlobalData::getInstance();

		// 获取当前时间点
		auto now = std::chrono::system_clock::now();
		// 转换为time_t格式
		std::time_t now_time = std::chrono::system_clock::to_time_t(now);
		// 转换为本地时间
		std::tm* local_time = std::localtime(&now_time);

		auto currentRunningState = globalData.runningState.load();
		switch (currentRunningState)
		{
		case RunningState::Debug:
			run_debug(frame);
			break;
		case RunningState::OpenRemoveFunc:
			run_OpenRemoveFunc(frame);
			break;
		default:
			break;
		}
	}
}

void ImageProcessor::run_debug(MatInfo& frame)
{
	auto& imgPro = *_imgProcess;
	imgPro(frame.image);
	auto maskImg = imgPro.getMaskImg(frame.image);
	auto defectResult = imgPro.getDefectResultInfo();

	drawKeyRange(maskImg, frame.image);

	emit imageReady(QPixmap::fromImage(maskImg));
}

void ImageProcessor::run_OpenRemoveFunc(MatInfo& frame)
{
	auto& imgPro = *_imgProcess;
	auto& qiXinShiJinConfig = GlobalData::getInstance().qiXinShiJinDanXiangJiConfig;
	double R1 = 0;
	double C1 = 0;
	double length = 0;
	double width = 0;
	double angle = 0;

	QFuture<bool> positiveIsBadFuture;

	positiveIsBadFuture = QtConcurrent::run(
		[this, &positiveIsBadFuture, &frame, &R1, &C1, &length, &width, &angle]() 
		{

		bool isBad = false;

		return isBad;
		});

	imgPro(frame.image);
	bool positiveIsBad{ false };

	positiveIsBadFuture.waitForFinished();
	positiveIsBad = positiveIsBadFuture.result();

	auto maskImg = imgPro.getMaskImg(frame.image);
	auto defectResult = imgPro.getDefectResultInfo();

	auto& context = _imgProcess->context();

	if (defectResult.isBad)
	{
		_isbad = true;
	}

	run_OpenRemoveFunc_emitErrorInfo(_isbad);

	drawLines(maskImg);

	emit imageNGReady(QPixmap::fromImage(maskImg), frame.index, defectResult.isBad);
	emit
}

void ImageProcessor::run_OpenRemoveFunc_emitErrorInfo(bool isbad) const
{
	auto& globalStruct = GlobalData::getInstance();
	auto& globalThread = GlobalThread::getInstance();

	if (isbad)
	{
		++globalStruct.statisticalInfo.wasteCount;
	}

	if (imageProcessingModuleIndex == 1 || imageProcessingModuleIndex == 2)
	{
		++globalStruct.statisticalInfo.produceCount;
	}

	if (isbad)
	{
		globalThread.priorityQueue->push(true);
	}
}

void ImageProcessor::buildSEGModelEngine(const QString& enginePath)
{
	rw::ModelEngineConfig modelEngineConfig;
	modelEngineConfig.conf_threshold = 0.1f;
	modelEngineConfig.nms_threshold = 0.1f;
	modelEngineConfig.imagePretreatmentPolicy = rw::ImagePretreatmentPolicy::LetterBox;
	modelEngineConfig.letterBoxColor = cv::Scalar(114, 114, 114);
	modelEngineConfig.modelPath = enginePath.toStdString();
	auto engine = rw::ModelEngineFactory::createModelEngine(modelEngineConfig, rw::ModelType::Yolov11_Seg_Mask, rw::ModelEngineDeployType::TensorRT);

	_imgProcess = std::make_unique<rw::imgPro::ImageProcess>(engine);

	iniIndexGetContext();
	iniEliminationInfoFunc();
	iniEliminationInfoGetContext();
	iniDefectResultInfoFunc();
	iniDefectResultGetContext();
	iniDefectDrawConfig();
	iniRunTextConfig();
}

void ImageProcessor::iniIndexGetContext()
{
	auto& context = _imgProcess->context();
}

void ImageProcessor::iniEliminationInfoFunc()
{
	updateParamMapsFromGlobalStruct();
}

void ImageProcessor::iniEliminationInfoGetContext()
{
	auto& context = _imgProcess->context();

	context.eliminationInfoGetContext.getEliminationItemFuncSpecialOperator = [this](rw::imgPro::EliminationItem& item,
		const rw::DetectionRectangleInfo& info,
		const rw::imgPro::EliminationInfoGetConfig& cfg) {

		};
}

void ImageProcessor::iniDefectResultInfoFunc()
{
	auto& context = _imgProcess->context();

	rw::imgPro::DefectResultInfoFunc::Config defectConfig;
	rw::imgPro::DefectResultInfoFunc::ClassIdWithConfigMap defectConfigs;
	defectConfig.isEnable = BodyMap["enable"];
	defectConfigs[ClassId::Body] = defectConfig;
	defectConfig.isEnable = ChiMap["enable"];
	defectConfigs[ClassId::Chi] = defectConfig;
	context.defectCfg = defectConfigs;
}

void ImageProcessor::iniDefectResultGetContext()
{
	auto& context = _imgProcess->context();
	context.defectResultGetContext.getDefectResultExtraOperate = [this](const rw::imgPro::EliminationItem& item, const rw::DetectionRectangleInfo& detectionRectangleInfo) {

		};
}

void ImageProcessor::iniDefectDrawConfig()
{
	auto& context = _imgProcess->context();

	rw::imgPro::DefectDrawFunc::ConfigDefectDraw drawConfig;
	updateDrawRec();
	drawConfig.classIdWithConfigMap[0].isDrawMask = true;
	drawConfig.classIdWithConfigMap[1].isDrawMask = true;
	drawConfig.classIdWithConfigMap[0].hasFrame = false;
	drawConfig.classIdWithConfigMap[1].hasFrame = false;

	drawConfig.classIdWithConfigMap[0].defectColorGood = rw::rqw::RQWColor::Green;
	drawConfig.classIdWithConfigMap[0].defectColorBad = rw::rqw::RQWColor::Green;
	drawConfig.classIdWithConfigMap[1].defectColorGood = rw::rqw::RQWColor::Red;
	drawConfig.classIdWithConfigMap[1].defectColorBad = rw::rqw::RQWColor::Red;

	drawConfig.classIdWithConfigMap[0].isDisAreaText = false;
	drawConfig.classIdWithConfigMap[0].isDisScoreText = false;
	drawConfig.classIdWithConfigMap[0].isDisName = false;
	drawConfig.classIdWithConfigMap[1].isDisAreaText = false;
	drawConfig.classIdWithConfigMap[1].isDisScoreText = false;
	drawConfig.classIdWithConfigMap[1].isDisName = false;
	context.defectDrawCfg = drawConfig;
}

void ImageProcessor::iniRunTextConfig()
{
	updateDrawText();
}

void ImageProcessor::drawLines(QImage& image)
{
	auto& setConfig = GlobalData::getInstance().setConfig;
	rw::imgPro::ConfigDrawLine configDrawLine;
	configDrawLine.color = rw::imgPro::Color::Red;
	configDrawLine.thickness = 3;

	double pixToWorld = setConfig.xiangsudangliang;
	if (pixToWorld <= 0.0) {
		return;
	}

	double yStart = setConfig.biaozhunxianshangjuli / pixToWorld;
	int num = setConfig.biaozhunxianshuliang;
	double yDifference = setConfig.biaozhunxianjiange / pixToWorld;

	if (num <= 0) {
		return;
	}

	for (int i = 0; i < num; ++i) {
		double y = yStart + i * yDifference;
		if (y < 0) {
			continue;
		}
		if (y >= image.height()) {
			break;
		}
		configDrawLine.position = y;
		rw::imgPro::ImagePainter::drawHorizontalLine(image, configDrawLine);
	}
}

void ImageProcessor::drawKeyRange(QImage& maskImg,const cv::Mat& rowImage)
{
	auto& imgPro = *_imgProcess;
	auto& setConfig = GlobalData::getInstance().setConfig;
	double pixToWorld = setConfig.xiangsudangliang;
	if (pixToWorld <= 0.0) {
		return;
	}

	double yStart = setConfig.biaozhunxianshangjuli / pixToWorld;
	int num = setConfig.biaozhunxianshuliang;
	double yDifference = setConfig.biaozhunxianjiange / pixToWorld;

	if (num <= 0) {
		return;
	}

	auto bodyIndexes = imgPro.getProcessResultIndexMap().at(ClassId::Body);
	auto chiIndedxes = imgPro.getProcessResultIndexMap().at(ClassId::Chi);

	if (0 == bodyIndexes.size() || 0 == chiIndedxes.size())
	{
		return;
	}

	int bodyIndex = 0;
	for (const auto& item : bodyIndexes)
	{
		bodyIndex = item;
	}
	int chiIndex = 0;
	for (const auto& item : chiIndedxes)
	{
		chiIndex = item;
	}


	auto proResult = imgPro.getProcessResult();

	for (int i = 0; i < num; ++i) {
		double y = yStart + i * yDifference;
		if (y < 0) {
			continue;
		}
		if (y >= rowImage.rows) {
			break;
		}
		auto loc = y;
		auto result = countKeyLinePixels(proResult[bodyIndex], proResult[chiIndex], loc, rowImage);
		if (0 != result.totalCount)
		{
			rw::imgPro::ConfigDrawSegment cfg;
			cfg.fontSize = 24;
			cfg.thickness = 5;
			cfg.textLocate = rw::imgPro::ConfigDrawSegment::TextLocate::Left;
			cfg.startPoint = { result.leftBladeRange.first, loc };
			cfg.endPoint = { result.leftBladeRange.second, loc };
			double dis = static_cast<double>(rw::imgPro::pointDistance(cfg.startPoint, cfg.endPoint) * pixToWorld);
			if (0 != dis)
			{
				cfg.text = QString::number(dis, 'f', 2);
				cfg.color = rw::imgPro::Color::Blue;
				rw::imgPro::ImagePainter::drawSegmentLine(maskImg, cfg);
			}

			cfg.textLocate = rw::imgPro::ConfigDrawSegment::TextLocate::Right;
			cfg.startPoint = { result.rightBladeRange.first, loc };
			cfg.endPoint = { result.rightBladeRange.second, loc };
			dis = static_cast<double>(rw::imgPro::pointDistance(cfg.startPoint, cfg.endPoint) * pixToWorld);
			if (0 != dis)
			{
				cfg.text = QString::number(dis, 'f', 2);
				cfg.color = rw::imgPro::Color::Blue;
				rw::imgPro::ImagePainter::drawSegmentLine(maskImg, cfg);
			}

			cfg.textLocate = rw::imgPro::ConfigDrawSegment::TextLocate::Middle;
			cfg.startPoint = { result.leftEmptyRange.first, loc };
			cfg.endPoint = { result.leftEmptyRange.second, loc };
			dis = static_cast<double>(rw::imgPro::pointDistance(cfg.startPoint, cfg.endPoint) * pixToWorld);
			if (0 != dis)
			{
				cfg.text = QString::number(dis, 'f', 2);
				cfg.color = rw::imgPro::Color::Orange;
				rw::imgPro::ImagePainter::drawSegmentLine(maskImg, cfg);
			}

			cfg.textLocate = rw::imgPro::ConfigDrawSegment::TextLocate::Middle;
			cfg.startPoint = { result.RightEmptyRange.first, loc };
			cfg.endPoint = { result.RightEmptyRange.second, loc };
			dis = static_cast<double>(rw::imgPro::pointDistance(cfg.startPoint, cfg.endPoint) * pixToWorld);
			if (0 != dis)
			{
				cfg.text = QString::number(dis, 'f', 2);
				cfg.color = rw::imgPro::Color::Orange;
				rw::imgPro::ImagePainter::drawSegmentLine(maskImg, cfg);
			}

			cfg.textLocate = rw::imgPro::ConfigDrawSegment::TextLocate::Middle;
			cfg.startPoint = { result.middleTeethRange.first, loc };
			cfg.endPoint = { result.middleTeethRange.second, loc };
			dis = static_cast<double>(rw::imgPro::pointDistance(cfg.startPoint, cfg.endPoint) * pixToWorld);
			if (0 != dis)
			{
				cfg.text = QString::number(dis, 'f', 2);
				cfg.color = rw::imgPro::Color::Gray;
				rw::imgPro::ImagePainter::drawSegmentLine(maskImg, cfg);
			}
		}
		else
		{
			rw::imgPro::ConfigDrawLine configDrawLine;
			configDrawLine.color = rw::imgPro::Color::Red;
			configDrawLine.thickness = 3;
			configDrawLine.position = y;
			rw::imgPro::ImagePainter::drawHorizontalLine(maskImg, configDrawLine);
		}
	}
}

void ImageProcessor::updateDrawRec()
{
	auto& globalStruct = GlobalData::getInstance();
	auto& context = _imgProcess->context();
	context.defectDrawCfg.isDrawMask = true;
	if (globalStruct.qiXinShiJinDanXiangJiConfig.isshibiekuang)
	{
		context.defectDrawCfg.isDrawDefects = true;
		context.defectDrawCfg.isDrawDisableDefects = true;
		context.defectDrawCfg.isDisAreaText = true;
		context.defectDrawCfg.isDisScoreText = true;
	}
	else
	{
		context.defectDrawCfg.isDrawDefects = false;
		context.defectDrawCfg.isDrawDisableDefects = false;
		context.defectDrawCfg.isDisAreaText = false;
		context.defectDrawCfg.isDisScoreText = false;
	}
}

void ImageProcessor::updateDrawText()
{
	auto& globalStruct = GlobalData::getInstance();
	auto& context = _imgProcess->context();
	if (globalStruct.qiXinShiJinDanXiangJiConfig.iswenzi)
	{
		context.runTextCfg.isDrawExtraText = true;
	}
	else
	{
		context.runTextCfg.isDrawExtraText = false;
	}
}

void ImageProcessor::updateParamMapsFromGlobalStruct()
{
	auto& context = _imgProcess->context();
	auto& globalStruct = GlobalData::getInstance();

	BodyMap["classId"] = ClassId::Body;
	BodyMap["maxArea"] = 0;
	BodyMap["maxScore"] = 0;
	BodyMap["enable"] = true;
	if (1 == imageProcessingModuleIndex)
	{
		BodyMap["pixToWorld"] = globalStruct.setConfig.xiangsudangliang;
	}

	ChiMap["classId"] = ClassId::Chi;
	ChiMap["maxArea"] = 0;
	ChiMap["maxScore"] = 0;
	ChiMap["enable"] = true;
	if (1 == imageProcessingModuleIndex)
	{
		ChiMap["pixToWorld"] = globalStruct.setConfig.xiangsudangliang;
	}

	rw::imgPro::EliminationInfoFunc::ClassIdWithConfigMap eliminationInfoGetConfigs;
	rw::imgPro::EliminationInfoGetConfig BodyEliminationInfoGetConfig;
	rw::imgPro::EliminationInfoGetConfig ChiEliminationInfoGetConfig;

	BodyEliminationInfoGetConfig.areaFactor = BodyMap["pixToWorld"];//这里设置为像素当量
	BodyEliminationInfoGetConfig.scoreFactor = 100;//这里设置为百分比当量
	BodyEliminationInfoGetConfig.isUsingArea = false;//这里设置为使用面积
	BodyEliminationInfoGetConfig.isUsingScore = true;//这里设置为使用分数
	BodyEliminationInfoGetConfig.scoreRange = { 0,BodyMap["maxScore"] };
	BodyEliminationInfoGetConfig.areaRange = { 0,BodyMap["maxArea"] };
	BodyEliminationInfoGetConfig.scoreIsUsingComplementarySet = false;
	eliminationInfoGetConfigs[ClassId::Body] = BodyEliminationInfoGetConfig;

	ChiEliminationInfoGetConfig.areaFactor = ChiMap["pixToWorld"];//这里设置为像素当量
	ChiEliminationInfoGetConfig.scoreFactor = 100;//这里设置为百分比当量
	ChiEliminationInfoGetConfig.isUsingArea = false;//这里设置为使用面积
	ChiEliminationInfoGetConfig.isUsingScore = true;//这里设置为使用分数
	ChiEliminationInfoGetConfig.scoreRange = { 0,ChiMap["maxScore"] };
	ChiEliminationInfoGetConfig.areaRange = { 0,ChiMap["maxArea"] };
	ChiEliminationInfoGetConfig.scoreIsUsingComplementarySet = false;
	eliminationInfoGetConfigs[ClassId::Chi] = ChiEliminationInfoGetConfig;

	context.eliminationCfg = eliminationInfoGetConfigs;

	iniDefectResultInfoFunc();
}

void ImageProcessingModule::BuildModule()
{
	for (int i = 0; i < _numConsumers; ++i) {
		static size_t workIndexCount = 0;
		ImageProcessor* processor = new ImageProcessor(_queue, _mutex, _condition, workIndexCount, this);
		workIndexCount++;
		processor->buildSEGModelEngine(modelEnginePath);
		processor->imageProcessingModuleIndex = index;
		connect(processor, &ImageProcessor::imageReady, this, &ImageProcessingModule::imageReady, Qt::QueuedConnection);
		connect(processor, &ImageProcessor::imageNGReady, this, &ImageProcessingModule::imageNGReady, Qt::QueuedConnection);

		connect(this, &ImageProcessingModule::shibiekuangChanged, processor, &ImageProcessor::updateDrawRec, Qt::QueuedConnection);
		connect(this, &ImageProcessingModule::wenziChanged, processor, &ImageProcessor::updateDrawText, Qt::QueuedConnection);
		connect(this, &ImageProcessingModule::paramMapsChanged, processor, &ImageProcessor::updateParamMapsFromGlobalStruct, Qt::QueuedConnection);
		_processors.push_back(processor);
		processor->start();
	}
}

ImageProcessingModule::ImageProcessingModule(int numConsumers, QObject* parent)
	: QObject(parent), _numConsumers(numConsumers)
{

}

ImageProcessingModule::~ImageProcessingModule()
{
	// 通知所有线程退出
	for (auto processor : _processors) {
		processor->requestInterruption();
	}

	// 唤醒所有等待的线程
	{
		QMutexLocker locker(&_mutex);
		_condition.wakeAll();
	}

	// 等待所有线程退出
	for (auto processor : _processors) {
		if (processor->isRunning()) {
			processor->wait(1000); // 使用超时机制，等待1秒
		}
		delete processor;
	}
}

void ImageProcessingModule::onFrameCaptured(rw::rqw::MatInfo matInfo, size_t index)
{
	// 手动读取本地图片
	//std::string imagePath = R"(C:\Users\zfkj4090\Desktop\yaoshi.bmp)"; // 替换为你的图片路径
	//cv::Mat frame1 = cv::imread(imagePath, cv::IMREAD_COLOR);
	//matInfo.mat = frame1.clone();
	if (matInfo.mat.channels() == 4) {
		cv::cvtColor(matInfo.mat, matInfo.mat, cv::COLOR_BGRA2BGR);
	}
	if (matInfo.mat.type() != CV_8UC3) {
		matInfo.mat.convertTo(matInfo.mat, CV_8UC3);
	}

	if (matInfo.mat.empty()) {
		return; // 跳过空帧
	}

	QMutexLocker locker(&_mutex);
	MatInfo mat;
	mat.image = matInfo.mat;
	mat.index = index;

	_queue.enqueue(mat);
	_condition.wakeOne();
}
