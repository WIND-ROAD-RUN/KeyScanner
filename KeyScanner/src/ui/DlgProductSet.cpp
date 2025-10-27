#include "DlgProductSet.h"
#include "ui_DlgProductSet.h"

#include <QMessageBox>
#include <QTabWidget>
#include <QtConcurrent/qtconcurrentrun.h>

#include "GlobalStruct.hpp"
#include "NumberKeyboard.h"

DlgProductSet::DlgProductSet(QWidget* parent)
	: QDialog(parent)
	, ui(new Ui::DlgProductSetClass())
{
	ui->setupUi(this);

	build_ui();

	build_connect();
}

DlgProductSet::~DlgProductSet()
{
	delete ui;
}

void DlgProductSet::build_ui()
{
	read_config();
}

void DlgProductSet::read_config()
{
	auto& setConfig = GlobalData::getInstance().setConfig;

	// 普通参数
	ui->btn_xiangsudangliang->setText(QString::number(setConfig.xiangsudangliang));
	ui->btn_zuobiaozhunxianjiange->setText(QString::number(setConfig.zuobiaozhunxianjiange));
	ui->btn_zuobiaozhunxianshangjuli->setText(QString::number(setConfig.zuobiaozhunxianshangjuli));
	ui->btn_zuobiaozhunxianshuliang->setText(QString::number(setConfig.zuobiaozhunxianshuliang));
	ui->btn_youbiaozhunxianjiange->setText(QString::number(setConfig.youbiaozhunxianjiange));
	ui->btn_youbiaozhunxianshangjuli->setText(QString::number(setConfig.youbiaozhunxianshangjuli));
	ui->btn_youbiaozhunxianshuliang->setText(QString::number(setConfig.youbiaozhunxianshuliang));
	// 相机参数
	ui->btn_baoguang->setText(QString::number(setConfig.baoguang));
	ui->btn_zengyi->setText(QString::number(setConfig.zengyi));
}

void DlgProductSet::build_connect()
{
	connect(ui->btn_close, &QPushButton::clicked, this, &DlgProductSet::btn_close_clicked);
	connect(ui->btn_xiangsudangliang, &QPushButton::clicked, this, &DlgProductSet::btn_xiangsudangliang_clicked);
	connect(ui->btn_zuobiaozhunxianjiange, &QPushButton::clicked, this, &DlgProductSet::btn_zuobiaozhunxianjiange_clicked);
	connect(ui->btn_zuobiaozhunxianshangjuli, &QPushButton::clicked, this, &DlgProductSet::btn_zuobiaozhunxianshangjuli_clicked);
	connect(ui->btn_zuobiaozhunxianshuliang, &QPushButton::clicked, this, &DlgProductSet::btn_zuobiaozhunxianshuliang_clicked);
	connect(ui->btn_youbiaozhunxianjiange, &QPushButton::clicked, this, &DlgProductSet::btn_youbiaozhunxianjiange_clicked);
	connect(ui->btn_youbiaozhunxianshangjuli, &QPushButton::clicked, this, &DlgProductSet::btn_youbiaozhunxianshangjuli_clicked);
	connect(ui->btn_youbiaozhunxianshuliang, &QPushButton::clicked, this, &DlgProductSet::btn_youbiaozhunxianshuliang_clicked);
	connect(ui->btn_baoguang, &QPushButton::clicked, this, &DlgProductSet::btn_baoguang_clicked);
	connect(ui->btn_zengyi, &QPushButton::clicked, this, &DlgProductSet::btn_zengyi_clicked);
}

void DlgProductSet::btn_close_clicked()
{
	auto& globalFunc = GlobalFuncObject::getInstance();

	globalFunc.saveSetConfig();
	emit paramsChanged();
	this->close();
}

void DlgProductSet::btn_xiangsudangliang_clicked()
{
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() <= 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的数值");
			return;
		}
		auto& setConfig = GlobalData::getInstance().setConfig;
		ui->btn_xiangsudangliang->setText(value);
		setConfig.xiangsudangliang = value.toDouble();
	}
}

void DlgProductSet::btn_zuobiaozhunxianjiange_clicked()
{
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() <= 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的数值");
			return;
		}
		auto& setConfig = GlobalData::getInstance().setConfig;
		ui->btn_zuobiaozhunxianjiange->setText(value);
		setConfig.zuobiaozhunxianjiange = value.toDouble();
	}
}

void DlgProductSet::btn_zuobiaozhunxianshangjuli_clicked()
{
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() <= 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的数值");
			return;
		}
		auto& setConfig = GlobalData::getInstance().setConfig;
		ui->btn_zuobiaozhunxianshangjuli->setText(value);
		setConfig.zuobiaozhunxianshangjuli = value.toDouble();
	}
}

void DlgProductSet::btn_zuobiaozhunxianshuliang_clicked()
{
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toInt() <= 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的整数值");
			return;
		}
		auto& setConfig = GlobalData::getInstance().setConfig;
		ui->btn_zuobiaozhunxianshuliang->setText(value);
		setConfig.zuobiaozhunxianshuliang = value.toInt();
	}
}

void DlgProductSet::btn_youbiaozhunxianjiange_clicked()
{
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() <= 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的数值");
			return;
		}
		auto& setConfig = GlobalData::getInstance().setConfig;
		ui->btn_youbiaozhunxianjiange->setText(value);
		setConfig.youbiaozhunxianjiange = value.toDouble();
	}
}

void DlgProductSet::btn_youbiaozhunxianshangjuli_clicked()
{
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() <= 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的数值");
			return;
		}
		auto& setConfig = GlobalData::getInstance().setConfig;
		ui->btn_youbiaozhunxianshangjuli->setText(value);
		setConfig.youbiaozhunxianshangjuli = value.toDouble();
	}
}

void DlgProductSet::btn_youbiaozhunxianshuliang_clicked()
{
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toInt() <= 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的整数值");
			return;
		}
		auto& setConfig = GlobalData::getInstance().setConfig;
		ui->btn_youbiaozhunxianshuliang->setText(value);
		setConfig.youbiaozhunxianshuliang = value.toInt();
	}
}

void DlgProductSet::btn_baoguang_clicked()
{
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于等于0的数值");
			return;
		}
		auto& setConfig = GlobalData::getInstance().setConfig;
		auto& camera = GlobalThread::getInstance().camera1;
		camera->setExposureTime(value.toInt());
		ui->btn_baoguang->setText(value);
		setConfig.baoguang = value.toDouble();
	}
}

void DlgProductSet::btn_zengyi_clicked()
{
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于等于0的数值");
			return;
		}
		auto& setConfig = GlobalData::getInstance().setConfig;
		auto& camera = GlobalThread::getInstance().camera1;
		camera->setGain(value.toInt());
		ui->btn_zengyi->setText(value);
		setConfig.zengyi = value.toDouble();
	}
}