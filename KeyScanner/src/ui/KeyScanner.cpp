#ifndef NOMINMAX
#define NOMINMAX
#endif

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

#ifdef BUILD_WITH_HALCON
#include "halconcpp/HalconCpp.h"
#endif

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

#ifdef BUILD_WITH_HALCON
	// 初始化 Halcon 显示
	initHalconDisplay();
#endif
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
	auto& qiXinShiJinDanXiangJiConfig = globalStruct.keyScannerConfig;
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

	globalFunc.storeContext->ensureFileExistsSafe(globalPath.keyScannerConfigPath.toStdString(), cdm::KeyScannerConfig());
	auto loadResult = globalFunc.storeContext->loadSafe(globalPath.keyScannerConfigPath.toStdString());
	if (!loadResult)
	{
		globalFunc.storeContext->saveSafe(cdm::KeyScannerConfig(), globalPath.keyScannerConfigPath.toStdString());
		return;
	}
	globalData.keyScannerConfig = *loadResult;
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
	// 启动PLC检测线程
	globalThread.detachCheckPlcController->startThread();
}

void KeyScanner::stop_Threads()
{
	auto& globalThread = GlobalThread::getInstance();

	globalThread.detachCheckPlcController->stopThread();

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

	build_DetachCheckPlcController();

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

	destroy_DetachCheckPlcController();

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
	QObject::connect(_dlgProductSet, &DlgProductSet::paramsChanged, globalThread.modelCamera1.get(), &ImageProcessingModule::paramMapsChanged);
	QObject::connect(&globalThread, &GlobalThread::emit_getSignal, globalThread.modelCamera1.get(), &ImageProcessingModule::getPlcSignal);
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

#ifdef BUILD_WITH_HALCON
void KeyScanner::initHalconDisplay()
{
	// 创建 HalconDisplay 对象，绑定到 label_imgDisplay_1 控件
	_halconDisplay = std::make_unique<rw::rqw::HalconDisplay>(ui->label_imgDisplay_1);
	
	// 初始化 Halcon 窗口
	if (_halconDisplay->initialize()) {
		qDebug() << "HalconDisplay: 初始化成功";
	}
	else {
		qWarning() << "HalconDisplay: 初始化失败";
	}
}
#endif

void KeyScanner::pbtn_limit_clicked()
{
	/*if (_dlgLimit)
	{
		_dlgLimit->setFixedSize(this->width(), this->height());
		_dlgLimit->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
		_dlgLimit->exec();
	}*/

#ifdef BUILD_WITH_HALCON
	// 使用 HalconDisplay 显示图片（窗口已在构造函数中初始化）
	if (_halconDisplay && _halconDisplay->isValid()) {
		// 图片路径（请根据实际情况修改）
		QString imagePath = "C:\\Users\\zfkj4090\\Desktop\\temp\\images\\OK20251225160441239.jpg";  // 修改为你的图片路径
		
		// 显示图片
		if (_halconDisplay->displayImageFromFile(imagePath, true)) {
			qDebug() << "Halcon: 图片显示成功";
		}
		else {
			QMessageBox::warning(this, "错误", "Halcon 显示图片失败");
		}
	}
	else {
		qWarning() << "HalconDisplay: 窗口未初始化，无法显示图片";
		QMessageBox::warning(this, "错误", "Halcon 窗口未初始化");
	}
#endif
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
			globalThread.camera1->setTriggerState(false);
			globalThread.camera1->setFrameRate(3);
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
	globalData.keyScannerConfig.isSaveImg = checked;
}

void KeyScanner::ckb_shibiekuang_checked(bool checked)
{
	auto& globalData = GlobalData::getInstance();
	globalData.keyScannerConfig.isshibiekuang = ui->ckb_shibiekuang->isChecked();
}

void KeyScanner::ckb_wenzi_checked(bool checked)
{
	auto& globalData = GlobalData::getInstance();
	globalData.keyScannerConfig.iswenzi = ui->ckb_wenzi->isChecked();
}

void KeyScanner::pbtn_resetProduct_clicked()
{
	auto& qiXinShiJinDanXiangJiConfig = GlobalData::getInstance().keyScannerConfig;

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

	checkFileExistAndFormat<cdm::KeyScannerConfig>(globalPath.keyScannerConfigPath, storageContext);
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

void KeyScanner::build_DetachCheckPlcController()
{
	GlobalThread::getInstance().build_DetachCheckPlcController();
}

void KeyScanner::destroy_DetachCheckPlcController()
{
	GlobalThread::getInstance().destroy_DetachCheckPlcController();
}

#ifdef BUILD_WITH_HALCON
bool KeyScanner::ensureHalconViewPart()
{
	if (!_halconLastImage)
		return false;

	try
	{
		HalconCpp::HTuple w, h;
		HalconCpp::GetImageSize(*_halconLastImage, &w, &h);
		const int imgW = w.I();
		const int imgH = h.I();
		if (imgW <= 0 || imgH <= 0)
			return false;

		if (!_viewPartValid || imgW != _viewImgW || imgH != _viewImgH)
		{
			_viewImgW = imgW;
			_viewImgH = imgH;
			resetHalconViewPartToFullImage();
		}
		return true;
	}
	catch (...)
	{
		return false;
	}
}

void KeyScanner::resetHalconViewPartToFullImage()
{
	_viewPart.r1 = 0.0;
	_viewPart.c1 = 0.0;
	_viewPart.r2 = std::max(0, _viewImgH - 1);
	_viewPart.c2 = std::max(0, _viewImgW - 1);
	_viewPartValid = true;
}

void KeyScanner::zoomHalconViewAt(const QPoint& hostPos, int steps)
{
	if (steps == 0)
		return;
	if (!ensureHalconViewPart())
		return;

	const int hostW = std::max(1, _halconHost ? _halconHost->width() : 1);
	const int hostH = std::max(1, _halconHost ? _halconHost->height() : 1);

	const double spanC = _viewPart.c2 - _viewPart.c1;
	const double spanR = _viewPart.r2 - _viewPart.r1;

	const double rx = (hostW > 1) ? (static_cast<double>(hostPos.x()) / static_cast<double>(hostW - 1)) : 0.5;
	const double ry = (hostH > 1) ? (static_cast<double>(hostPos.y()) / static_cast<double>(hostH - 1)) : 0.5;

	const double col = _viewPart.c1 + rx * spanC;
	const double row = _viewPart.r1 + ry * spanR;

	const double base = 1.2;
	const double scale = std::pow(base, -steps);

	double newSpanC = spanC * scale;
	double newSpanR = spanR * scale;

	const double eps = 1e-6;
	if (std::abs(newSpanC) < eps) newSpanC = (newSpanC >= 0.0) ? eps : -eps;
	if (std::abs(newSpanR) < eps) newSpanR = (newSpanR >= 0.0) ? eps : -eps;

	const double fullSpanC = std::max(0, _viewImgW - 1);
	const double fullSpanR = std::max(0, _viewImgH - 1);
	if (newSpanC >= fullSpanC || newSpanR >= fullSpanR)
	{
		resetHalconViewPartToFullImage();
		return;
	}

	_viewPart.c1 = col - rx * newSpanC;
	_viewPart.r1 = row - ry * newSpanR;

	const double maxC1 = fullSpanC - newSpanC;
	const double maxR1 = fullSpanR - newSpanR;
	_viewPart.c1 = std::clamp(_viewPart.c1, 0.0, std::max(0.0, maxC1));
	_viewPart.r1 = std::clamp(_viewPart.r1, 0.0, std::max(0.0, maxR1));

	_viewPart.c2 = _viewPart.c1 + newSpanC;
	_viewPart.r2 = _viewPart.r1 + newSpanR;
	_viewPartValid = true;
}

void KeyScanner::panHalconViewFromDrag(const QPoint& dragDelta)
{
	if (!ensureHalconViewPart())
		return;

	const int hostW = std::max(1, _halconHost ? _halconHost->width() : 1);
	const int hostH = std::max(1, _halconHost ? _halconHost->height() : 1);

	const double spanC = _panStartPart.c2 - _panStartPart.c1;
	const double spanR = _panStartPart.r2 - _panStartPart.r1;

	const double dx = static_cast<double>(dragDelta.x());
	const double dy = static_cast<double>(dragDelta.y());

	const double dCol = (hostW > 1) ? (-(dx / static_cast<double>(hostW - 1)) * spanC) : 0.0;
	const double dRow = (hostH > 1) ? (-(dy / static_cast<double>(hostH - 1)) * spanR) : 0.0;

	_viewPart = _panStartPart;
	_viewPart.c1 += dCol;
	_viewPart.c2 += dCol;
	_viewPart.r1 += dRow;
	_viewPart.r2 += dRow;

	const double fullSpanC = std::max(0, _viewImgW - 1);
	const double fullSpanR = std::max(0, _viewImgH - 1);
	const double curSpanC = _viewPart.c2 - _viewPart.c1;
	const double curSpanR = _viewPart.r2 - _viewPart.r1;
	if (curSpanC > 1e-9 && curSpanR > 1e-9)
	{
		const double maxC1 = fullSpanC - curSpanC;
		const double maxR1 = fullSpanR - curSpanR;
		_viewPart.c1 = std::clamp(_viewPart.c1, 0.0, std::max(0.0, maxC1));
		_viewPart.r1 = std::clamp(_viewPart.r1, 0.0, std::max(0.0, maxR1));
		_viewPart.c2 = _viewPart.c1 + curSpanC;
		_viewPart.r2 = _viewPart.r1 + curSpanR;
	}
	_viewPartValid = true;
}

bool KeyScanner::ensureHalconWindow()
{
	if (!_halconHost)
		return false;

	if (_halconWindowHandle && _halconWindowHandle->TupleLength() > 0)
		return true;

	if (!_halconWindowHandle)
		_halconWindowHandle = new HalconCpp::HTuple();

	QString err;
	const Hlong parentId = static_cast<Hlong>(_halconHost->winId());
	const HalconCpp::HTuple father(parentId);

	QSize hostSize = _halconHost->size();
	if (hostSize.isEmpty())
		hostSize = _labelImgDisplaySize;
	const int hostW = std::max(1, hostSize.width());
	const int hostH = std::max(1, hostSize.height());

	HalconCpp::OpenWindow(0, 0, hostW, hostH, father, "visible", "", _halconWindowHandle);

	return true;
}

void KeyScanner::closeHalconWindow()
{
	try
	{
		if (_halconWindowHandle && _halconWindowHandle->TupleLength() > 0)
		{
			HalconCpp::CloseWindow(*_halconWindowHandle);
		}
	}
	catch (...)
	{
	}

	delete _halconWindowHandle;
	_halconWindowHandle = nullptr;

	delete _halconLastImage;
	_halconLastImage = nullptr;

	delete _centerPointXldObj;
	_centerPointXldObj = nullptr;

	_viewPartValid = false;
	_viewImgW = 0;
	_viewImgH = 0;
	_isPanning = false;
}

void KeyScanner::redrawHalconView(bool clearWindow)
{
	if (!ensureHalconWindow())
		return;
	if (!_halconLastImage)
		return;
	if (!ensureHalconViewPart())
		return;

	const qreal dpr = _halconHost ? _halconHost->devicePixelRatioF() : 1.0;
	const int winW = std::max(1, static_cast<int>(std::lround((_halconHost ? _halconHost->width() : width()) * dpr)));
	const int winH = std::max(1, static_cast<int>(std::lround((_halconHost ? _halconHost->height() : height()) * dpr)));
	try
	{
		HalconCpp::SetWindowExtents(*_halconWindowHandle, 0, 0, winW, winH);
	}
	catch (...)
	{
	}

	try
	{
		using namespace HalconCpp;
		if (clearWindow)
			ClearWindow(*_halconWindowHandle);

		HalconViewPart partToShow = _viewPart;
		const double partW = partToShow.c2 - partToShow.c1;
		const double partH = partToShow.r2 - partToShow.r1;
		const double eps = 1e-9;
		if (partW > eps && partH > eps)
		{
			const double winAspect = (winH > 0) ? (static_cast<double>(winW) / static_cast<double>(winH)) : 1.0;
			const double partAspect = partW / partH;
			if (winAspect > partAspect)
			{
				const double newW = partH * winAspect;
				const double pad = (newW - partW) * 0.5;
				partToShow.c1 -= pad;
				partToShow.c2 += pad;
			}
			else if (winAspect < partAspect)
			{
				const double newH = partW / winAspect;
				const double pad = (newH - partH) * 0.5;
				partToShow.r1 -= pad;
				partToShow.r2 += pad;
			}
		}

		SetPart(*_halconWindowHandle, partToShow.r1, partToShow.c1, partToShow.r2, partToShow.c2);
		DispObj(*_halconLastImage, *_halconWindowHandle);
	}
	catch (...)
	{
		return;
	}

	try
	{
		using namespace HalconCpp;

		SetDraw(*_halconWindowHandle, "margin");
		SetLineWidth(*_halconWindowHandle, 2);

		auto dispRois = [&](const char* color, const HalconCpp::HObject* obj)
			{
				if (!obj)
					return;

				HTuple n;
				CountObj(*obj, &n);
				const int count = n.I();
				if (count <= 0)
					return;

				SetColor(*_halconWindowHandle, color);

				for (int i = 1; i <= count; ++i)
				{
					HObject one;
					SelectObj(*obj, &one, i);
					DispObj(one, *_halconWindowHandle);
				}
			};

		dispRois("green", _processParam._paintCreateRoiObj);
		dispRois("red", _processParam._paintShieldRoiObj);

		if (_processParam._findCreateXldObj)
		{
			HTuple n;
			CountObj(*_processParam._findCreateXldObj, &n);
			if (n.I() > 0)
			{
				SetColor(*_halconWindowHandle, "cyan");
				SetLineWidth(*_halconWindowHandle, 2);
				DispObj(*_processParam._findCreateXldObj, *_halconWindowHandle);
			}
		}

		if (_centerPointXldObj)
		{
			HTuple n;
			CountObj(*_centerPointXldObj, &n);
			if (n.I() > 0)
			{
				SetColor(*_halconWindowHandle, "yellow");
				SetLineWidth(*_halconWindowHandle, 2);
				DispObj(*_centerPointXldObj, *_halconWindowHandle);
			}
		}
	}
	catch (...)
	{
	}
}
#endif // BUILD_WITH_HALCON
