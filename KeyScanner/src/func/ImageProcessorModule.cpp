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
	
}

void ImageProcessor::run_OpenRemoveFunc(MatInfo& frame)
{

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

void ImageProcessor::save_image(rw::rqw::ImageInfo& imageInfo, const QImage& image)
{
	save_image_work(imageInfo, image);
}

void ImageProcessor::save_image_work(rw::rqw::ImageInfo& imageInfo, const QImage& image)
{
	auto& imageSaveEngine = GlobalThread::getInstance().imageSaveEngine;
	auto& config = GlobalData::getInstance().keyScannerConfig;
	if (config.isSaveImg)
	{
		imageInfo.classify = "OK";
		imageSaveEngine->pushImage(imageInfo);
	}
}

void ImageProcessor::processKeyRange()
{
	auto& limitConfig = GlobalData::getInstance().limitConfig;

	// 处理左侧 keyRange
	processKeyRangeSide(leftKeyRange,
		limitConfig.neichi1zuoxiaxian, limitConfig.neichi1zuoshangxian,
		limitConfig.neichi2zuoxiaxian, limitConfig.neichi2zuoshangxian,
		limitConfig.neichi3zuoxiaxian, limitConfig.neichi3zuoshangxian,
		limitConfig.neichi4zuoxiaxian, limitConfig.neichi4zuoshangxian);

	// 处理右侧 keyRange
	processKeyRangeSide(rightKeyRange,
		limitConfig.neichi1youxiaxian, limitConfig.neichi1youshangxian,
		limitConfig.neichi2youxiaxian, limitConfig.neichi2youshangxian,
		limitConfig.neichi3youxiaxian, limitConfig.neichi3youshangxian,
		limitConfig.neichi4youxiaxian, limitConfig.neichi4youshangxian);
}

void ImageProcessor::processKeyRangeSide(std::vector<rw::hoem::UInt16>& keyRange, int neichi1Lower, int neichi1Upper,
	int neichi2Lower, int neichi2Upper, int neichi3Lower, int neichi3Upper, int neichi4Lower, int neichi4Upper)
{
	for (auto& value : keyRange)
	{
		if (0 == value)
		{
			// 为0则不处理
		}
		else if (value >= neichi1Lower && value <= neichi1Upper)
		{
			value = 1;
		}
		else if (value >= neichi2Lower && value <= neichi2Upper)
		{
			value = 2;
		}
		else if (value >= neichi3Lower && value <= neichi3Upper)
		{
			value = 3;
		}
		else if (value >= neichi4Lower && value <= neichi4Upper)
		{
			value = 4;
		}
		else
		{
			value = 0; // 异常值
		}
	}
}

void ImageProcessor::sendKeyRange()
{
	auto plcControllerScheduler = GlobalThread::getInstance().plcController.plcControllerScheduler;
	if (!plcControllerScheduler)
	{
		return;
	}

	auto isLeftSuccess = plcControllerScheduler->writeUInt16RegistersAsync(700, leftKeyRange, 2, std::chrono::milliseconds(500));
	auto isRightSuccess = plcControllerScheduler->writeUInt16RegistersAsync(720, rightKeyRange, 2, std::chrono::milliseconds(500));

	if (isLeftSuccess.get() && isRightSuccess.get())
	{
		qDebug() << "PLC写入左右键槽成功";
	}
	else
	{
		qDebug() << "PLC写入左右键槽失败";
	}
}

void ImageProcessor::resetCoil()
{
	auto plcControllerScheduler = GlobalThread::getInstance().plcController.plcControllerScheduler;
	if (!plcControllerScheduler)
	{
		return;
	}

	try
	{
		// 重置线圈状态为 false
		auto writeResult = plcControllerScheduler->writeCoilAsync(188, false,
			2, std::chrono::milliseconds(500));

		if (writeResult.get())
		{
			qDebug() << "PLC线圈复位成功";
		}
	}
	catch (const std::exception& e)
	{
		qWarning() << "PLC operation failed:" << e.what();
		auto plcController = GlobalThread::getInstance().plcController.plcController;
		auto isReconnect = plcController->reconnect();
		if (isReconnect)
		{
			qDebug() << "PLC重新连接成功";
		}
	}
}

void ImageProcessor::updateParamMapsFromGlobalStruct()
{

}

void ImageProcessor::getPlcSignal()
{
	_canPlcGetMessage = true;
}

void ImageProcessingModule::BuildModule()
{
	for (int i = 0; i < _numConsumers; ++i) {
		static size_t workIndexCount = 0;
		ImageProcessor* processor = new ImageProcessor(_queue, _mutex, _condition, workIndexCount, this);
		workIndexCount++;
		processor->imageProcessingModuleIndex = index;
		connect(processor, &ImageProcessor::imageReady, this, &ImageProcessingModule::imageReady, Qt::QueuedConnection);
		connect(processor, &ImageProcessor::imageNGReady, this, &ImageProcessingModule::imageNGReady, Qt::QueuedConnection);

		connect(this, &ImageProcessingModule::paramMapsChanged, processor, &ImageProcessor::updateParamMapsFromGlobalStruct, Qt::QueuedConnection);
		connect(this, &ImageProcessingModule::getPlcSignal, processor, &ImageProcessor::getPlcSignal);

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
