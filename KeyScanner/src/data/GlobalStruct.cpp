#include "GlobalStruct.hpp"

#include <QDir>

#include "KeyScanner.h"
#include "Utilty.hpp"
#include <QRegularExpression>

GlobalThread& GlobalThread::getInstance()
{
	static GlobalThread instance;
	return instance;
}

GlobalThread::GlobalThread()
{
}

GlobalThread::~GlobalThread()
{
}

void GlobalThread::buildCamera()
{
	buildCamera1();
}

void GlobalThread::destroyCamera()
{
	destroyCamera1();
}

bool GlobalThread::buildCamera1()
{
	auto cameraList = rw::rqw::CheckCameraList();

	auto cameraMetaData1 = cameraMetaDataCheck(Utility::cameraIp1, cameraList);

	auto& globalDataSetConfig = GlobalData::getInstance().setConfig;

	if (cameraMetaData1.ip != "0")
	{
		try
		{
			camera1 = std::make_unique<rw::rqw::CameraPassiveThread>(this);
			camera1->initCamera(cameraMetaData1, rw::rqw::CameraObjectTrigger::Hardware);
			camera1->setTriggerState(false);
			camera1->cameraIndex = 1;
			camera1->setFrameRate(3);
			camera1->setHeartbeatTime(5000);
			camera1->setExposureTime(static_cast<size_t>(globalDataSetConfig.baoguang));
			camera1->setGain(static_cast<size_t>(globalDataSetConfig.zengyi));

			QObject::connect(camera1.get(), &rw::rqw::CameraPassiveThread::frameCaptured,
				modelCamera1.get(), &ImageProcessingModule::onFrameCaptured, Qt::DirectConnection);

			return true;
		}
		catch (const std::exception&)
		{
			return false;
		}
	}
	return false;
}

void GlobalThread::destroyCamera1()
{
	QObject::disconnect(camera1.get(), &rw::rqw::CameraPassiveThread::frameCaptured,
		modelCamera1.get(), &ImageProcessingModule::onFrameCaptured);
	camera1.reset();
}

void GlobalThread::buildImageProcessorModules(const QString& path)
{
	modelCamera1 = std::make_unique<ImageProcessingModule>(1);

	modelCamera1->modelEnginePath = path;

	modelCamera1->index = 1;

	modelCamera1->BuildModule();
}

void GlobalThread::destroyImageProcessingModule()
{
	modelCamera1.reset();
}

void GlobalThread::build_PriorityQueue()
{
	auto compareNodeEqual = [](const float& a, const float& b) {
		return a == b;
		};
	auto compareNodePriority = [](const float& a, const float& b) {
		return a < b;
		};

	priorityQueue = std::make_unique<rw::dsl::ThreadSafeHeap<bool>>();
}

void GlobalThread::destroy_PriorityQueue()
{
	priorityQueue.reset();
}

void GlobalThread::build_DetachDefectThread()
{
	detachDefectThread = new DetachDefectThread(this);
}

void GlobalThread::destroy_DetachDefectThread()
{
	if (detachDefectThread)
	{
		delete detachDefectThread;
		detachDefectThread = nullptr;
	}
}

void GlobalThread::build_DetachUtiltyThread()
{
	detachUtiltyThread = new DetachUtiltyThread(this);
}

void GlobalThread::destroy_DetachUtiltyThread()
{
	if (detachUtiltyThread)
	{
		delete detachUtiltyThread;
		detachUtiltyThread = nullptr;
	}
}

void GlobalThread::build_CameraAndCardStateThread()
{
	cameraAndCardStateThread = new CameraAndCardStateThread(this);
	// 更新UI界面
	QObject::connect(cameraAndCardStateThread, &CameraAndCardStateThread::updateCameraLabelState,
		this, &GlobalThread::emit_updateUiLabels, Qt::QueuedConnection);
	// 相机重连
	QObject::connect(cameraAndCardStateThread, &CameraAndCardStateThread::buildCamera1,
		this, &GlobalThread::rebuild_Camera1, Qt::QueuedConnection);
	// 相机销毁
	QObject::connect(cameraAndCardStateThread, &CameraAndCardStateThread::destroyCamera1,
		this, &GlobalThread::destroy_Camera1, Qt::QueuedConnection);
	// 运动控制器重连
	QObject::connect(cameraAndCardStateThread, &CameraAndCardStateThread::buildZMotion,
		this, &GlobalThread::rebuild_ZMotion, Qt::QueuedConnection);
	// 运动控制器销毁
	QObject::connect(cameraAndCardStateThread, &CameraAndCardStateThread::destroyZMotion,
		this, &GlobalThread::destroy_ZMotion, Qt::QueuedConnection);
}

void GlobalThread::destroy_CameraAndCardStateThread()
{
	if (cameraAndCardStateThread)
	{
		delete cameraAndCardStateThread;
		cameraAndCardStateThread = nullptr;
	}
}

bool GlobalThread::build_ZMotion()
{
	zmotion = std::make_shared<rw::rqw::ZMotion>(Utility::zmotionIp);
	zmotion->setIp(Utility::zmotionIp);
	bool isConnected = zmotion->connect();
	return isConnected;
}

void GlobalThread::Destroy_ZMotion()
{
	if (zmotion)
	{
		bool isDisconnect = zmotion->disConnect();
		zmotion.reset();
	}
}

void GlobalThread::build_ImageSaveEngine()
{
	{
		QString imageSavePath = globalPath.imageSaveRootPath;
		QVector<QString> sortedFolders;

		// 打开指定路径
		QDir dir(imageSavePath);
		if (!dir.exists()) {
			return;
		}

		// 设置过滤器，只获取文件夹
		dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);

		// 获取文件夹列表
		QFileInfoList folderList = dir.entryInfoList();

		// 存储文件夹及其日期
		QVector<QPair<QDate, QString>> dateFolderPairs;

		for (const QFileInfo& folderInfo : folderList) {
			QString folderName = folderInfo.fileName();

			// 尝试解析文件夹名称为日期
			QDate folderDate = QDate::fromString(folderName, "yyyy_MM_dd");
			if (folderDate.isValid()) {
				dateFolderPairs.append(qMakePair(folderDate, folderName));
			}
		}

		// 按日期排序
		std::sort(dateFolderPairs.begin(), dateFolderPairs.end(),
			[](const QPair<QDate, QString>& a, const QPair<QDate, QString>& b) {
				return a.first < b.first;
			});

		// 提取排序后的文件夹名称
		for (const auto& pair : dateFolderPairs) {
			sortedFolders.append(pair.second);
		}

		// 删除超过7天的文件夹
		QDate currentDate = QDate::currentDate();
		for (const QString& folderName : sortedFolders) {
			QDate folderDate = QDate::fromString(folderName, "yyyy_MM_dd");
			if (folderDate.isValid() && folderDate < currentDate.addDays(-7)) {
				QString folderPath = imageSavePath + folderName;
				QDir(folderPath).removeRecursively();
			}
		}
	}

	imageSaveEngine = std::make_unique<rw::rqw::ImageSaveEngine>(this, 4);

	imageSaveEngine->setSaveImgFormat(rw::rqw::ImageSaveFormat::JPEG);
	imageSaveEngine->setSaveImgQuality(80);
	QDir dir;
	QString imageSavePath = globalPath.imageSaveRootPath;

	QString currentDate = QDate::currentDate().toString("yyyy_MM_dd");
	QString imageSaveEnginePath = imageSavePath + currentDate;

	QString imagesFilePathFilePathFull = dir.absoluteFilePath(imageSaveEnginePath);
	imageSaveEngine->setRootPath(imagesFilePathFilePathFull);
	imageSaveEngine->setSavePolicy(rw::rqw::ImageSaveEnginePolicy::MaxSaveImageNum);
	imageSaveEngine->setMaxSaveImageNum(9999);

	imageSaveEngine->startEngine();
}

void GlobalThread::destroy_ImageSaveEngine()
{
	if (imageSaveEngine)
	{
		imageSaveEngine->stop();
		imageSaveEngine.reset();
	}
}

void GlobalThread::build_PlcController()
{
	plcController.build_plcController();
}

void GlobalThread::destroy_PlcController()
{
	plcController.destroy_plcController();
}

void GlobalThread::build_DetachCheckPlcController()
{
	detachCheckPlcController = new DetachCheckPlcController(this);

	QObject::connect(detachCheckPlcController, &DetachCheckPlcController::getSignal,
		this, &GlobalThread::emit_getSignal);
}

void GlobalThread::destroy_DetachCheckPlcController()
{
	if (detachCheckPlcController)
	{
		delete detachCheckPlcController;
		detachCheckPlcController = nullptr;
	}
}

void GlobalThread::rebuild_Camera1()
{
	buildCamera1();
	if (camera1)
	{
		camera1->startMonitor();
	}
}

void GlobalThread::destroy_Camera1()
{
	destroyCamera1();
}

void GlobalThread::rebuild_ZMotion()
{
	build_ZMotion();
}

void GlobalThread::destroy_ZMotion()
{
	Destroy_ZMotion();
}

GlobalFuncObject& GlobalFuncObject::getInstance()
{
	static GlobalFuncObject instance;
	return instance;
}

GlobalFuncObject::GlobalFuncObject()
{
}

GlobalFuncObject::~GlobalFuncObject()
{
}

GlobalData::GlobalData()
{

}

GlobalData::~GlobalData()
{

}

void GlobalFuncObject::buildConfigManager(rw::oso::StorageType type)
{
	storeContext = std::make_unique<rw::oso::StorageContext>(type);
}

void GlobalFuncObject::saveQiXinShiJinDanXiangJiConfig()
{
	auto& globalStruct = GlobalData::getInstance();
	std::string generalConfigPath = globalPath.keyScannerConfigPath.toStdString();
	storeContext->saveSafe(globalStruct.keyScannerConfig, generalConfigPath);
}

void GlobalFuncObject::saveSetConfig()
{
	auto& globalStruct = GlobalData::getInstance();
	std::string setConfigPath = globalPath.setConfigPath.toStdString();
	storeContext->saveSafe(globalStruct.setConfig, setConfigPath);
}

void GlobalFuncObject::saveLimitConfig()
{
	auto& globalStruct = GlobalData::getInstance();
	std::string limitConfigPath = globalPath.limitConfigPath.toStdString();
	storeContext->saveSafe(globalStruct.limitConfig, limitConfigPath);
}

bool GlobalThread::isTargetCamera(const QString& cameraIndex, const QString& targetName)
{
	QRegularExpression regex(R"((\d+)\.(\d+)\.(\d+)\.(\d+))");
	QRegularExpressionMatch match = regex.match(targetName);

	if (match.hasMatch()) {
		auto matchString = match.captured(3);

		return cameraIndex == matchString;
	}

	return false;
}

rw::rqw::CameraMetaData GlobalThread::cameraMetaDataCheck(const QString& cameraIndex,
	const QVector<rw::rqw::CameraMetaData>& cameraInfo)
{
	for (const auto& cameraMetaData : cameraInfo) {
		if (isTargetCamera(cameraIndex, cameraMetaData.ip)) {
			return cameraMetaData;
		}
	}
	rw::rqw::CameraMetaData error;
	error.ip = "0";
	return error;
}

#ifdef BUILD_WITHOUT_HARDWARE
void GlobalThread::build_TestImgPushThread()
{
	testImgPushThread = std::make_unique<TestImgPushThread>();
	testImgPushThread->startThread();
}

void GlobalThread::destroy_TestImgPushThread()
{
	testImgPushThread->stopThread();
	testImgPushThread.reset();
}
#endif
