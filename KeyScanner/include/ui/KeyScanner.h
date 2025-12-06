#pragma once

#include <QMainWindow>
#include <memory>
#include <QCheckBox>

#include "DlgProductSet.h"
#include "rqw_LabelClickable.h"
#include "DlgCloseForm.h"
#include "oso_func.hpp"
#include "oso_StorageContext.hpp"
#include "rqw_RunEnvCheck.hpp"
#include "DlgLimit.h"
#include "PlcController.hpp"
#include <QSpinBox>

QT_BEGIN_NAMESPACE
namespace Ui { class KeyScannerClass; };
QT_END_NAMESPACE

class KeyScanner : public QMainWindow
{
	Q_OBJECT
#ifdef BUILD_WITHOUT_HARDWARE
private:
	QCheckBox* _testIfPushImg;
	QSpinBox* _pushImgTime;
public slots:
	void cbox_testIfPushImg_clicked(bool states);
	void sBox_pushImgTime_valueChanged(int value);
#endif

public:
	KeyScanner(QWidget* parent = nullptr);
	~KeyScanner();
public:
	void build_ui();
	void build_connect();
	void build_KeyScannerData();
	void build_DlgProductSet();
	void ini_clickableTitle();
	void build_DlgCloseForm();
	void build_DlgLimitForm();
public:
	void read_config();
	void read_config_KeyScannerConfig();
	void read_config_DlgProductSetConfig();
	void read_config_DlgLimitConfig();
public:
	void save_config();
public:
	void start_Threads();
	void stop_Threads();
public:
	void initializeComponents();
	void destroyComponents();
public:
	void build_camera();
	void start_camera();
	void destroy_camera();
public:
	void build_ImageProcessingModule();
	void destroy_ImageProcessingModule();
public:
	void build_CameraAndBoardReconnectThread();
	void destroy_CameraAndBoardReconnectThread();
public:
	void build_PriorityQueue();
	void destroy_PriorityQueue();
public:
	void build_DetachDefectThread();
	void destroy_DetachDefectThread();
public:
	void build_DetachUtiltyThread();
	void destroy_DetachUtiltyThread();
public:
	void build_zmotion();
	void destroy_zmotion();
public:
	void build_imageSaveEngine();
	void destroy_imageSaveEngine();
private slots:
	void updateCameraLabelState(int cameraIndex, bool state);

	void onUpdateStatisticalInfoUI();

	void onCamera1Display(QPixmap image);

	void onCameraNGDisplay(QPixmap image, size_t index, bool isbad);

	void lb_title_clicked();
private slots:
	void pbtn_exit_clicked();
	void pbtn_set_clicked();
	void pbtn_limit_clicked();
	void rbtn_debug_checked(bool checked);
	void rbtn_removeFunc_checked(bool checked);
	void rbtn_saveImg_checked(bool checked);
	void ckb_shibiekuang_checked(bool checked);
	void ckb_wenzi_checked(bool checked);
	void pbtn_resetProduct_clicked();

signals:
	void shibiekuangChanged();
	void wenziChanged();

public:
	static bool check();
	template<class TypeCanToAssembly>
	static void checkFileExistAndFormat(const QString& path, const rw::oso::StorageContext& context);
	static bool EnsureDirectoryExists(const QString& dirPath);
private:
	rw::rqw::ClickableLabel* clickableTitle = nullptr;
public:
	DlgProductSet* _dlgProductSet = nullptr;
	DlgCloseForm* _dlgCloseForm = nullptr;
	DlgLimit* _dlgLimit = nullptr;
private:
	Ui::KeyScannerClass* ui;
	int minimizeCount{ 3 };


	// PLC通讯
	PlcController plcController;
	void build_PlcController();
	void destroy_PlcController();
};

template <class TypeCanToAssembly>
void KeyScanner::checkFileExistAndFormat(const QString& path, const rw::oso::StorageContext& context)
{
	if (rw::rqw::RunEnvCheck::isFileExist(path))
	{
		if (!rw::rqw::RunEnvCheck::isFileFormatCorrectWithSafe<TypeCanToAssembly>(path, context))
		{
			auto assembly = context.load(path.toStdString());
			bool isMerge{ false };
			auto mergeAssembly = rw::oso::AssemblyMergeTool::Merge(TypeCanToAssembly(), *assembly, isMerge);
			if (isMerge)
			{
				context.saveSafe(mergeAssembly, path.toStdString());
			}
			else
			{
				context.saveSafe(TypeCanToAssembly(), path.toStdString());
			}
		}
	}
	else
	{
		context.saveSafe(TypeCanToAssembly(), path.toStdString());
	}
}

