#pragma once

#include"ime_ModelEngineFactory.h"

#include <QObject>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>
#include <opencv2/opencv.hpp>
#include <vector>
#include <QThread>
#include <QPixmap>
#include <imgPro_ImageProcess.hpp>

#include "hoem_utilty.hpp"
#include "rqw_CameraObjectCore.hpp"
#include "rqw_ImageSaveEngine.h"

struct KeyLinePixelCountResult {
	int leftBladeCount = 0;
	int rightBladeCount = 0;
	int middleTeethCount = 0;
	int totalCount = 0;
	int bladeTotalCount = 0;
	std::pair<int, int> leftEmptyRange{0,0};
	std::pair<int, int> RightEmptyRange{ 0,0 };
	std::pair<int, int> keyRange{0,0};
	std::pair<int, int> leftBladeRange{0,0};
	std::pair<int, int> rightBladeRange{0,0};
	std::pair<int, int> middleTeethRange{0,0};
};

KeyLinePixelCountResult countKeyLinePixels(
	const rw::DetectionRectangleInfo& blade,
	const rw::DetectionRectangleInfo& teeth,
	int lineY,
	const cv::Mat & mat);

// 图片信息
struct MatInfo {
	cv::Mat image;	// 图片内容
	float location;	// 记录拍照瞬间的时间点
	size_t index;	// 拍照的相机的下标
};


class ImageProcessor : public QThread
{
	Q_OBJECT

public:
	ImageProcessor(QQueue<MatInfo>& queue,
		QMutex& mutex,
		QWaitCondition& condition,
		int workIndex,
		QObject* parent = nullptr);

protected:
	void run() override;

private:
	void run_debug(MatInfo& frame);				// 不开剔废时候的调试模式
private:
	void run_OpenRemoveFunc(MatInfo& frame);	// 开启剔废功能时的处理模式

	void run_OpenRemoveFunc_emitErrorInfo(bool isbad) const;

private:
	// 存图
	void save_image(rw::rqw::ImageInfo& imageInfo, const QImage& image);
	void save_image_work(rw::rqw::ImageInfo& imageInfo, const QImage& image);

signals:
	void imageReady(QPixmap image);
	void imageNGReady(QPixmap image, size_t index, bool isbad);

private:
	std::unique_ptr<rw::imgPro::ImageProcess> _imgProcess;
public:
	// 构建模型引擎
	void buildSEGModelEngine(const QString& enginePath);

	void iniIndexGetContext();
	void iniEliminationInfoFunc();
	void iniEliminationInfoGetContext();
	void iniDefectResultInfoFunc();
	void iniDefectResultGetContext();
	void iniDefectDrawConfig();
	void iniRunTextConfig();


public:
	void drawKeyRange(QImage& maskImg, const cv::Mat& rowImage, std::vector<rw::hoem::UInt16>& leftKeyRange, std::vector<rw::hoem::UInt16>&
	                  rightKeyRange);

	void drawLeftKeyRange(QImage& maskImg, const cv::Mat& rowImage, const rw::imgPro::ProcessResult& processResult, const int& bodyIndex, const int& chiIndex, std
	                      ::vector<rw::hoem::UInt16>& leftKeyRange);
	void drawRightKeyRange(QImage& maskImg, const cv::Mat& rowImage, const rw::imgPro::ProcessResult& processResult, const int& bodyIndex, const int& chiIndex, std
	                       ::vector<rw::hoem::UInt16>& rightKeyRange);

	void processKeyRange();
	void processKeyRangeSide(std::vector<rw::hoem::UInt16>& keyRange,
	                         int neichi1Lower, int neichi1Upper,
	                         int neichi2Lower, int neichi2Upper,
	                         int neichi3Lower, int neichi3Upper,
	                         int neichi4Lower, int neichi4Upper);

	void sendKeyRange();
public slots:
	void updateDrawRec();
	void updateDrawText();
	void updateParamMapsFromGlobalStruct();

	// 收到PLC信号
	void getPlcSignal();
public:
	bool _isbad{ false };

	bool _canPlcGetMessage{ false };
private:
	std::map<std::string, double> BodyMap{};
	std::map<std::string, double> ChiMap{};

	std::vector<rw::hoem::UInt16> leftKeyRange{};
	std::vector<rw::hoem::UInt16> rightKeyRange{};
private:
	QQueue<MatInfo>& _queue;
	QMutex& _mutex;
	QWaitCondition& _condition;
	int _workIndex;
public:
	int imageProcessingModuleIndex;
};


class ImageProcessingModule : public QObject {
	Q_OBJECT
public:
	QString modelEnginePath;

public:
	// 初始化图像处理模块
	void BuildModule();
public:
	ImageProcessingModule(int numConsumers, QObject* parent = nullptr);

	~ImageProcessingModule();

public slots:
	// 相机回调函数
	void onFrameCaptured(rw::rqw::MatInfo matInfo, size_t index);

signals:
	void imageReady(QPixmap image);
	void imageNGReady(QPixmap image, size_t index, bool isbad);
	void shibiekuangChanged();
	void wenziChanged();
	void paramMapsChanged();

	// 收到PLC信号
	void getPlcSignal();
public:
	std::vector<ImageProcessor*> getProcessors() const {
		return _processors;
	}

private:
	QQueue<MatInfo> _queue;
	QMutex _mutex;
	QWaitCondition _condition;
	std::vector<ImageProcessor*> _processors;
	int _numConsumers;
public:
	size_t index;
};


