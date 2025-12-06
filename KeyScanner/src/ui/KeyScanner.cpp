#include "KeyScanner.h"

#include <QDir>
#include <QMessageBox>
#include <QProcess>

#include "ui_KeyScanner.h"
#include <QPushButton>
#include "GlobalStruct.hpp"
#include "NumberKeyboard.h"
#include "rqw_RunEnvCheck.hpp"
#include "Utilty.hpp"


#ifdef BUILD_WITHOUT_HARDWARE
void KeyScanner::cbox_testIfPushImg_clicked(bool states)
{
	GlobalThread::getInstance().testImgPush = states;
}

void KeyScanner::sBox_pushImgTime_valueChanged(int value)
{
	auto& globalThread = GlobalThread::getInstance();
	if (globalThread.testImgPushThread)
	{
		globalThread.testImgPushThread->setPushImgTime(value);
	}
}
#endif


KeyScanner::KeyScanner(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::KeyScannerClass())
{
	ui->setupUi(this);

	initializeComponents();
}

KeyScanner::~KeyScanner()
{
	destroyComponents();
	delete ui;
}

void KeyScanner::build_ui()
{
	build_KeyScannerData();
	build_DlgProductSet();
	build_DlgCloseForm();
	build_DlgLimitForm();
}

void KeyScanner::build_connect()
{
	QObject::connect(ui->pbtn_exit, &QPushButton::clicked,
		this, &KeyScanner::pbtn_exit_clicked);
	QObject::connect(ui->pbtn_set, &QPushButton::clicked,
		this, &KeyScanner::pbtn_set_clicked);
	QObject::connect(ui->pbtn_limit, &QPushButton::clicked,
		this, &KeyScanner::pbtn_limit_clicked);
	QObject::connect(ui->rbtn_debug, &QRadioButton::clicked,
		this, &KeyScanner::rbtn_debug_checked);
	QObject::connect(ui->rbtn_removeFunc, &QRadioButton::clicked,
		this, &KeyScanner::rbtn_removeFunc_checked);
	QObject::connect(ui->rbtn_saveImg, &QRadioButton::clicked,
		this, &KeyScanner::rbtn_saveImg_checked);
	QObject::connect(ui->ckb_shibiekuang, &QCheckBox::clicked,
		this, &KeyScanner::ckb_shibiekuang_checked);
	QObject::connect(ui->ckb_wenzi, &QCheckBox::clicked,
		this, &KeyScanner::ckb_wenzi_checked);
	QObject::connect(ui->pbtn_resetProduct, &QPushButton::clicked,
		this, &KeyScanner::pbtn_resetProduct_clicked);
	// 连接显示标题
	QObject::connect(clickableTitle, &rw::rqw::ClickableLabel::clicked,
		this, &KeyScanner::lb_title_clicked);
}

void KeyScanner::build_KeyScannerData()
{
	auto& globalStruct = GlobalData::getInstance();
	auto& qiXinShiJinDanXiangJiConfig = globalStruct.qiXinShiJinDanXiangJiConfig;
	qiXinShiJinDanXiangJiConfig.isDebug = false;
	qiXinShiJinDanXiangJiConfig.isDefect = true;		// 默认开启剔废
	qiXinShiJinDanXiangJiConfig.isshibiekuang = true;
	qiXinShiJinDanXiangJiConfig.iswenzi = false;

	ui->label_produceTotalValue->setText(QString::number(qiXinShiJinDanXiangJiConfig.totalProductionVolume));
	ui->label_wasteProductsValue->setText(QString::number(qiXinShiJinDanXiangJiConfig.totalDefectiveVolume));
	ui->rbtn_removeFunc->setChecked(qiXinShiJinDanXiangJiConfig.isDefect);
	rbtn_removeFunc_checked(qiXinShiJinDanXiangJiConfig.isDefect);
	ui->ckb_shibiekuang->setChecked(qiXinShiJinDanXiangJiConfig.isshibiekuang);
	ui->ckb_wenzi->setChecked(qiXinShiJinDanXiangJiConfig.iswenzi);
	ui->rbtn_saveImg->setChecked(qiXinShiJinDanXiangJiConfig.isSaveImg);
	ini_clickableTitle();
}

void KeyScanner::build_DlgProductSet()
{
	_dlgProductSet = new DlgProductSet(this);
}

void KeyScanner::ini_clickableTitle()
{
	// 初始化标题label
	clickableTitle = new rw::rqw::ClickableLabel(this);
	auto layoutTitle = ui->groupBox_head->layout();
	layoutTitle->replaceWidget(ui->label_title, clickableTitle);
	delete ui->label_title;
	clickableTitle->setText("钥匙检测");
	clickableTitle->setStyleSheet("QLabel {font-size: 30px;font-weight: bold;color: rgb(255, 255, 255);padding: 5px 5px;border-bottom: 2px solid #cccccc;}");
}

void KeyScanner::build_DlgCloseForm()
{
	_dlgCloseForm = new DlgCloseForm(this);
}

void KeyScanner::build_DlgLimitForm()
{
	_dlgLimit = new DlgLimit(this);
}

void KeyScanner::read_config()
{
	auto& globalFuncObject = GlobalFuncObject::getInstance();
	globalFuncObject.buildConfigManager(rw::oso::StorageType::Xml);

	read_config_KeyScannerConfig();
	read_config_DlgProductSetConfig();
	read_config_DlgLimitConfig();
}

void KeyScanner::read_config_KeyScannerConfig()
{
	auto& globalFunc = GlobalFuncObject::getInstance();
	auto& globalData = GlobalData::getInstance();

	globalFunc.storeContext->ensureFileExistsSafe(globalPath.qiXinShiJinDanXiangJiConfigPath.toStdString(), cdm::QiXinShiJinDanXiangJiConfig());
	auto loadResult = globalFunc.storeContext->loadSafe(globalPath.qiXinShiJinDanXiangJiConfigPath.toStdString());
	if (!loadResult)
	{
		globalFunc.storeContext->saveSafe(cdm::QiXinShiJinDanXiangJiConfig(), globalPath.qiXinShiJinDanXiangJiConfigPath.toStdString());
		return;
	}
	globalData.qiXinShiJinDanXiangJiConfig = *loadResult;
}

void KeyScanner::read_config_DlgProductSetConfig()
{
	auto& globalFunc = GlobalFuncObject::getInstance();
	auto& globalData = GlobalData::getInstance();

	globalFunc.storeContext->ensureFileExistsSafe(globalPath.setConfigPath.toStdString(), cdm::SetConfig());
	auto loadResult = globalFunc.storeContext->loadSafe(globalPath.setConfigPath.toStdString());
	if (!loadResult)
	{
		globalFunc.storeContext->saveSafe(cdm::SetConfig(), globalPath.setConfigPath.toStdString());
		return;
	}
	globalData.setConfig = *loadResult;
}

void KeyScanner::read_config_DlgLimitConfig()
{
	auto& globalFunc = GlobalFuncObject::getInstance();
	auto& globalData = GlobalData::getInstance();
	globalFunc.storeContext->ensureFileExistsSafe(globalPath.limitConfigPath.toStdString(), cdm::LimitConfig());
	auto loadResult = globalFunc.storeContext->loadSafe(globalPath.limitConfigPath.toStdString());
	if (!loadResult)
	{
		globalFunc.storeContext->saveSafe(cdm::LimitConfig(), globalPath.limitConfigPath.toStdString());
		return;
	}
	globalData.limitConfig = *loadResult;
}

void KeyScanner::save_config()
{
	auto& globalFuncObject = GlobalFuncObject::getInstance();

	globalFuncObject.saveQiXinShiJinDanXiangJiConfig();
	globalFuncObject.saveSetConfig();
	globalFuncObject.saveLimitConfig();
}

void KeyScanner::start_Threads()
{
	auto& globalThread = GlobalThread::getInstance();
	// 启动异步剔废线程
	globalThread.detachDefectThread->startThread();
	// 启动相机重连线程
	globalThread.cameraAndCardStateThread->startThread();
	// 启动异步统计线程
	globalThread.detachUtiltyThread->startThread();
}

void KeyScanner::stop_Threads()
{
	auto& globalThread = GlobalThread::getInstance();

	globalThread.detachDefectThread->stopThread();

	globalThread.cameraAndCardStateThread->stopThread();

	globalThread.detachUtiltyThread->stopThread();
}

void KeyScanner::initializeComponents()
{
	read_config();

	build_ui();

	build_ImageProcessingModule();

	build_camera();

	build_zmotion();

	build_PlcController();

	build_PriorityQueue();

	build_DetachDefectThread();

	build_DetachUtiltyThread();

	build_imageSaveEngine();

	build_CameraAndBoardReconnectThread();

	build_connect();

	start_Threads();

	

#ifdef BUILD_WITHOUT_HARDWARE
	auto& globalThread = GlobalThread::getInstance();
	_testIfPushImg = new QCheckBox(this);
	_testIfPushImg->setText("图像推送状态");
	ui->gBox_infor->layout()->addWidget(_testIfPushImg);
	QObject::connect(_testIfPushImg, &QCheckBox::clicked,
		this, &KeyScanner::cbox_testIfPushImg_clicked);

	_pushImgTime = new QSpinBox(this);
	_pushImgTime->setRange(50, 2000);
	_pushImgTime->setSingleStep(50);
	_pushImgTime->setValue(150);
	ui->gBox_infor->layout()->addWidget(_pushImgTime);
	QObject::connect(_pushImgTime, &QSpinBox::valueChanged,
		this, &KeyScanner::sBox_pushImgTime_valueChanged);


	globalThread.testImgPushThread = std::make_unique<TestImgPushThread>(this);
	QObject::connect(globalThread.testImgPushThread.get(), &TestImgPushThread::imgReady,
		globalThread.modelCamera1.get(), &ImageProcessingModule::onFrameCaptured);

	globalThread.testImgPushThread->startThread();
#endif

}

void KeyScanner::destroyComponents()
{
#ifdef BUILD_WITHOUT_HARDWARE
	auto& globalThread = GlobalThread::getInstance();
	globalThread.testImgPushThread->stopThread();
	globalThread.testImgPushThread.reset();
#endif

	

	stop_Threads();

	destroy_CameraAndBoardReconnectThread();

	destroy_DetachUtiltyThread();

	destroy_imageSaveEngine();

	destroy_DetachDefectThread();

	destroy_PriorityQueue();

	destroy_ImageProcessingModule();

	destroy_PlcController();

	destroy_zmotion();

	destroy_camera();

	save_config();
}

void KeyScanner::build_camera()
{
	auto& globalThread = GlobalThread::getInstance();

	auto build1Result = globalThread.buildCamera1();
	updateCameraLabelState(1, build1Result);
	start_camera();
}

void KeyScanner::start_camera()
{
	auto& globalThread = GlobalThread::getInstance();
	if (globalThread.camera1 != nullptr)
	{
		globalThread.camera1->startMonitor();
	}
}

void KeyScanner::destroy_camera()
{
	auto& globalThread = GlobalThread::getInstance();
	globalThread.destroyCamera();
}

void KeyScanner::build_ImageProcessingModule()
{
	auto& globalThread = GlobalThread::getInstance();
	auto& globalData = GlobalData::getInstance();

	QDir dir;

	QString enginePathFull = globalPath.modelPath;

	QFileInfo engineFile(enginePathFull);

	if (!engineFile.exists()) {
		QMessageBox::critical(this, "Error", "Engine file or Name file does not exist. The application will now exit.");
		QApplication::quit();
		return;
	}

	globalThread.buildImageProcessorModules(enginePathFull);

	QObject::connect(globalThread.modelCamera1.get(), &ImageProcessingModule::imageReady, this, &KeyScanner::onCamera1Display);
	QObject::connect(globalThread.modelCamera1.get(), &ImageProcessingModule::imageNGReady, this, &KeyScanner::onCameraNGDisplay);
	QObject::connect(this, &KeyScanner::shibiekuangChanged, globalThread.modelCamera1.get(), &ImageProcessingModule::shibiekuangChanged);
	QObject::connect(this, &KeyScanner::wenziChanged, globalThread.modelCamera1.get(), &ImageProcessingModule::wenziChanged);
	QObject::connect(_dlgProductSet, &DlgProductSet::paramsChanged, globalThread.modelCamera1.get(), &ImageProcessingModule::paramMapsChanged);
}

void KeyScanner::destroy_ImageProcessingModule()
{
	auto& globalThread = GlobalThread::getInstance();
	globalThread.destroyImageProcessingModule();
}

void KeyScanner::build_CameraAndBoardReconnectThread()
{
	auto& globalThread = GlobalThread::getInstance();
	globalThread.build_CameraAndCardStateThread();

	QObject::connect(&globalThread, &GlobalThread::emit_updateUiLabels,
		this, &KeyScanner::updateCameraLabelState);
}

void KeyScanner::destroy_CameraAndBoardReconnectThread()
{
	auto& globalThread = GlobalThread::getInstance();
	globalThread.destroy_CameraAndCardStateThread();
}

void KeyScanner::build_PriorityQueue()
{
	auto& globalThread = GlobalThread::getInstance();
	globalThread.build_PriorityQueue();
}

void KeyScanner::destroy_PriorityQueue()
{
	auto& globalThread = GlobalThread::getInstance();
	globalThread.destroy_PriorityQueue();
}

void KeyScanner::build_DetachDefectThread()
{
	auto& globalThread = GlobalThread::getInstance();
	globalThread.build_DetachDefectThread();
}

void KeyScanner::destroy_DetachDefectThread()
{
	auto& globalThread = GlobalThread::getInstance();
	globalThread.destroy_DetachDefectThread();
}

void KeyScanner::build_DetachUtiltyThread()
{
	auto& globalThread = GlobalThread::getInstance();
	globalThread.build_DetachUtiltyThread();

	// 连接统计信息更新信号槽
	QObject::connect(globalThread.detachUtiltyThread, &DetachUtiltyThread::updateStatisticalInfo,
		this, &KeyScanner::onUpdateStatisticalInfoUI);
}

void KeyScanner::destroy_DetachUtiltyThread()
{
	auto& globalThread = GlobalThread::getInstance();
	globalThread.destroy_DetachUtiltyThread();
}

void KeyScanner::build_zmotion()
{
	auto& globalThread = GlobalThread::getInstance();
	auto buildResult = globalThread.build_ZMotion();

	updateCameraLabelState(0, buildResult);
}

void KeyScanner::destroy_zmotion()
{
	auto& globalThread = GlobalThread::getInstance();
	globalThread.Destroy_ZMotion();
}

void KeyScanner::build_imageSaveEngine()
{
	auto& globalThread = GlobalThread::getInstance();
	globalThread.build_ImageSaveEngine();
}

void KeyScanner::destroy_imageSaveEngine()
{
	auto& globalThread = GlobalThread::getInstance();
	globalThread.destroy_ImageSaveEngine();
}

void KeyScanner::updateCameraLabelState(int cameraIndex, bool state)
{
	auto& setConfig = GlobalData::getInstance().setConfig;
	switch (cameraIndex)
	{
	case 0:
		if (state) {
			ui->label_cardState->setText("连接成功");
			ui->label_cardState->setStyleSheet(QString("QLabel{color:rgb(0, 230, 0);font-size: 18px;font - weight: bold;padding: 5px 5px;} "));
		}
		else {
			ui->label_cardState->setText("连接失败");
			ui->label_cardState->setStyleSheet(QString("QLabel{color:rgb(230, 0, 0);font-size: 18px;font - weight: bold;padding: 5px 5px;} "));
		}
		break;
	case 1:
		if (state) {
			ui->label_camera1State->setText("连接成功");
			ui->label_camera1State->setStyleSheet(QString("QLabel{color:rgb(0, 230, 0);font-size: 18px;font - weight: bold;padding: 5px 5px;} "));
		}
		else {
			ui->label_camera1State->setText("连接失败");
			ui->label_camera1State->setStyleSheet(QString("QLabel{color:rgb(230, 0, 0);font-size: 18px;font - weight: bold;padding: 5px 5px;} "));
		}
		break;
	default:
		break;
	}
}

void KeyScanner::onUpdateStatisticalInfoUI()
{
	auto& statisticalInfo = GlobalData::getInstance().statisticalInfo;
	ui->label_produceTotalValue->setText(QString::number(statisticalInfo.produceCount.load()));
	ui->label_wasteProductsValue->setText(QString::number(statisticalInfo.wasteCount.load()));
}

void KeyScanner::onCamera1Display(QPixmap image)
{
	ui->label_imgDisplay_1->setPixmap(image.scaled(ui->label_imgDisplay_1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void KeyScanner::onCameraNGDisplay(QPixmap image, size_t index, bool isbad)
{
	ui->label_imgDisplay_1->setPixmap(image.scaled(ui->label_imgDisplay_1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void KeyScanner::lb_title_clicked()
{
	if (0 != minimizeCount)
	{
		minimizeCount--;
	}
	else if (0 >= minimizeCount)
	{
		// 最小化主窗体
		this->showMinimized();

		// 最小化所有子窗体（如果已创建且可见）
		if (_dlgProductSet && _dlgProductSet->isVisible())
			_dlgProductSet->showMinimized();

		minimizeCount = 3; // 重置最小化计数器
	}

}

void KeyScanner::pbtn_exit_clicked()
{
#ifdef NDEBUG
	if (_dlgCloseForm)
	{
		_dlgCloseForm->exec();
	}
#else
	this->close();
#endif
}

void KeyScanner::pbtn_set_clicked()
{
	if (_dlgProductSet)
	{
		_dlgProductSet->setFixedSize(this->width(), this->height());
		_dlgProductSet->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
		_dlgProductSet->exec();
	}
}

void KeyScanner::pbtn_limit_clicked()
{
	if (_dlgLimit)
	{
		_dlgLimit->setFixedSize(this->width(), this->height());
		_dlgLimit->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
		_dlgLimit->exec();
	}
}

void KeyScanner::rbtn_debug_checked(bool checked)
{
	auto isRuning = ui->rbtn_removeFunc->isChecked();

	auto& globalThread = GlobalThread::getInstance();
	auto& globalData = GlobalData::getInstance();
	if (!isRuning) {
		if (checked) {
			globalData.runningState = RunningState::Debug;
			if (globalThread.camera1)
			{
				globalThread.camera1->setTriggerState(false);
				globalThread.camera1->setFrameRate(3);
			}
		}
		else {
			globalData.runningState = RunningState::Stop;
		}
		ui->ckb_shibiekuang->setVisible(checked);
		ui->ckb_wenzi->setVisible(checked);
	}
	else {
		ui->rbtn_debug->setChecked(false);
	}
}

void KeyScanner::rbtn_removeFunc_checked(bool checked)
{
	auto& globalData = GlobalData::getInstance();
	auto& globalThread = GlobalThread::getInstance();
	if (checked)
	{
		globalData.runningState = RunningState::OpenRemoveFunc;
		if (globalThread.camera1)
		{
			globalThread.camera1->setTriggerState(true);
			globalThread.camera1->setFrameRate(50);
		}
		ui->rbtn_debug->setChecked(false);
		ui->ckb_shibiekuang->setVisible(false);
		ui->ckb_wenzi->setVisible(false);
	}
	else
	{
		globalData.runningState = RunningState::Stop;
	}
}

void KeyScanner::rbtn_saveImg_checked(bool checked)
{
	auto& globalData = GlobalData::getInstance();
	globalData.qiXinShiJinDanXiangJiConfig.isSaveImg = checked;
}

void KeyScanner::ckb_shibiekuang_checked(bool checked)
{
	auto& globalData = GlobalData::getInstance();
	globalData.qiXinShiJinDanXiangJiConfig.isshibiekuang = ui->ckb_shibiekuang->isChecked();

	emit shibiekuangChanged();
}

void KeyScanner::ckb_wenzi_checked(bool checked)
{
	auto& globalData = GlobalData::getInstance();
	globalData.qiXinShiJinDanXiangJiConfig.iswenzi = ui->ckb_wenzi->isChecked();

	emit wenziChanged();
}

void KeyScanner::pbtn_resetProduct_clicked()
{
	auto& qiXinShiJinDanXiangJiConfig = GlobalData::getInstance().qiXinShiJinDanXiangJiConfig;

	qiXinShiJinDanXiangJiConfig.totalProductionVolume = 0;
	qiXinShiJinDanXiangJiConfig.totalDefectiveVolume = 0;

	onUpdateStatisticalInfoUI();
}

bool KeyScanner::check()
{
#pragma region check single instance
	if (!rw::rqw::RunEnvCheck::isSingleInstance("KeyScanner.exe"))
	{
		QMessageBox::warning(nullptr, "错误", "已经有程序在运行，请勿多次打开");
		return false;
	}
#pragma endregion

#pragma region check run env
	if (rw::rqw::RunEnvCheck::isProcessRunning("MVS.exe"))
	{
		QMessageBox::warning(nullptr, "错误", "检测到海康威视软件正在运行，请先关闭后再启动本程序。");
		return false;
	}

	if (rw::rqw::RunEnvCheck::isProcessRunning("BasedCam3.exe"))
	{
		QMessageBox::warning(nullptr, "错误", "检测到度申相机平台软件正在运行，请先关闭后再启动本程序。");
		return false;
	}
#pragma endregion

#pragma region check directory exist
	EnsureDirectoryExists(globalPath.projectHome);
	EnsureDirectoryExists(globalPath.configRootPath);
	EnsureDirectoryExists(globalPath.modelRootPath);
	EnsureDirectoryExists(globalPath.imageSaveRootPath);
#pragma endregion

#pragma region check model exist
	if (!rw::rqw::RunEnvCheck::isFileExist(globalPath.modelPath))
	{
		QMessageBox::warning(nullptr, "错误", "模型文件缺失");
		return false;
	}
#pragma endregion

#pragma region check config format and exist
	rw::oso::StorageContext storageContext(rw::oso::StorageType::Xml);

	checkFileExistAndFormat<cdm::QiXinShiJinDanXiangJiConfig>(globalPath.qiXinShiJinDanXiangJiConfigPath, storageContext);
	checkFileExistAndFormat<cdm::SetConfig>(globalPath.setConfigPath, storageContext);
	checkFileExistAndFormat<cdm::LimitConfig>(globalPath.limitConfigPath, storageContext);
#pragma endregion

	return true;
}

bool KeyScanner::EnsureDirectoryExists(const QString& dirPath)
{
	QDir dir(dirPath);
	if (!dir.exists()) {
		return dir.mkpath(".");
	}
	return true;
}

void KeyScanner::build_PlcController()
{
	GlobalThread::getInstance().build_PlcController();
}

void KeyScanner::destroy_PlcController()
{
	GlobalThread::getInstance().destroy_PlcController();
}
