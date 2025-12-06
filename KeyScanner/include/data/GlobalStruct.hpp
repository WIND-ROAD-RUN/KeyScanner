#pragma once

#include <qobject.h>

#include "DetachDefectThread.h"
#include "DetachUtiltyThread.h"
#include "dsl_Heap.hpp"
#include "KeyScannerConfig.hpp"
#include "SetConfig.hpp"
#include "oso_StorageContext.hpp"
#include "rqw_CameraObjectThread.hpp"
#include "rqw_ImageSaveEngine.h"
#include "ImageProcessorModule.hpp"
#include "CameraAndCardStateThread.h"
#include "rqw_ZMotion.hpp"
#include "LimitConfig.hpp"
#include "TestImgPushThread.hpp"
#include "PlcController.hpp"


enum class RunningState
{
	Debug,
	OpenRemoveFunc,
	Stop
};

class GlobalThread
	:public QObject
{
	Q_OBJECT
public:
	static GlobalThread& getInstance();

	GlobalThread(const GlobalThread&) = delete;
	GlobalThread& operator=(const GlobalThread&) = delete;
private:
	GlobalThread();
	~GlobalThread() override;
public:
	std::unique_ptr<rw::rqw::CameraPassiveThread> camera1{ nullptr };
	void buildCamera();
	bool buildCamera1();

	void destroyCamera();
	void destroyCamera1();
public:
	// 图像处理模块
	std::unique_ptr<ImageProcessingModule> modelCamera1 = nullptr;

	void buildImageProcessorModules(const QString& path);
	void destroyImageProcessingModule();
public:
	std::unique_ptr<rw::dsl::ThreadSafeHeap<bool>> priorityQueue;

	void build_PriorityQueue();
	void destroy_PriorityQueue();
public:
	DetachDefectThread* detachDefectThread;

	void build_DetachDefectThread();
	void destroy_DetachDefectThread();
public:
	DetachUtiltyThread* detachUtiltyThread;

	void build_DetachUtiltyThread();
	void destroy_DetachUtiltyThread();
public:
	CameraAndCardStateThread* cameraAndCardStateThread;
public:
	void build_CameraAndCardStateThread();
	void destroy_CameraAndCardStateThread();
public:
	std::shared_ptr<rw::rqw::ZMotion> zmotion{ nullptr };

	bool build_ZMotion();
	void Destroy_ZMotion();
public:
	// 图像保存引擎
	std::unique_ptr<rw::rqw::ImageSaveEngine> imageSaveEngine{ nullptr };
	void build_ImageSaveEngine();
	void destroy_ImageSaveEngine();
public:
	// PLC模块
	PlcController plcController;
	void build_PlcController();
	void destroy_PlcController();
signals:
	// 更新UI
	void emit_updateUiLabels(int index, bool isConnected);
public slots:
	// 相机重连
	void rebuild_Camera1();
	void destroy_Camera1();
	// 运动控制器重连
	void rebuild_ZMotion();
	void destroy_ZMotion();
public:
	bool isTargetCamera(const QString& cameraIndex, const QString& targetName);
	rw::rqw::CameraMetaData cameraMetaDataCheck(const QString& cameraIndex, const QVector<rw::rqw::CameraMetaData>& cameraInfo);

#ifdef BUILD_WITHOUT_HARDWARE
public:
	std::unique_ptr<TestImgPushThread> testImgPushThread{ nullptr };
	std::atomic_bool testImgPush{ false };

	void build_TestImgPushThread();
	void destroy_TestImgPushThread();
#endif
};

class GlobalFuncObject
	:public QObject
{
	Q_OBJECT
public:
	static GlobalFuncObject& getInstance();

	GlobalFuncObject(const GlobalFuncObject&) = delete;
	GlobalFuncObject& operator=(const GlobalFuncObject&) = delete;
private:
	GlobalFuncObject();
	~GlobalFuncObject() override;
public:
	std::unique_ptr<rw::oso::StorageContext> storeContext{ nullptr };
	void buildConfigManager(rw::oso::StorageType type);
	void saveQiXinShiJinDanXiangJiConfig();
	void saveSetConfig();
	void saveLimitConfig();
};

class GlobalData
	:public QObject
{
	Q_OBJECT
public:
	static GlobalData& getInstance()
	{
		static GlobalData instance;
		return instance;
	}

	GlobalData(const GlobalData&) = delete;
	GlobalData& operator=(const GlobalData&) = delete;
private:
	GlobalData();
	~GlobalData() override;
public:
	std::atomic<RunningState> runningState{ RunningState::OpenRemoveFunc };
public:
	// 统计信息
	struct StatisticalInfo
	{
		std::atomic_uint64_t produceCount{ 0 };
		std::atomic_uint64_t wasteCount{ 0 };
	} statisticalInfo;

public:
	cdm::QiXinShiJinDanXiangJiConfig qiXinShiJinDanXiangJiConfig;
	cdm::SetConfig setConfig;
	cdm::LimitConfig limitConfig;
};