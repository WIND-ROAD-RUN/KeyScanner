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
	ui->btn_biaozhunxianjiange->setText(QString::number(setConfig.biaozhunxianjiange));
	ui->btn_biaozhunxianshangjuli->setText(QString::number(setConfig.biaozhunxianshangjuli));
	ui->btn_biaozhunxianshuliang->setText(QString::number(setConfig.biaozhunxianshuliang));
	// 相机参数
	ui->btn_baoguang->setText(QString::number(setConfig.baoguang));
	ui->btn_zengyi->setText(QString::number(setConfig.zengyi));
}

void DlgProductSet::build_connect()
{
	connect(ui->btn_close, &QPushButton::clicked, this, &DlgProductSet::btn_close_clicked);
	connect(ui->btn_xiangsudangliang, &QPushButton::clicked, this, &DlgProductSet::btn_xiangsudangliang_clicked);
	connect(ui->btn_biaozhunxianjiange, &QPushButton::clicked, this, &DlgProductSet::btn_biaozhunxianjiange_clicked);
	connect(ui->btn_biaozhunxianshangjuli, &QPushButton::clicked, this, &DlgProductSet::btn_biaozhunxianshangjuli_clicked);
	connect(ui->btn_biaozhunxianshuliang, &QPushButton::clicked, this, &DlgProductSet::btn_biaozhunxianshuliang_clicked);
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

void DlgProductSet::btn_biaozhunxianjiange_clicked()
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
		ui->btn_biaozhunxianjiange->setText(value);
		setConfig.biaozhunxianjiange = value.toDouble();
	}
}

void DlgProductSet::btn_biaozhunxianshangjuli_clicked()
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
		ui->btn_biaozhunxianshangjuli->setText(value);
		setConfig.biaozhunxianshangjuli = value.toDouble();
	}
}

void DlgProductSet::btn_biaozhunxianshuliang_clicked()
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
		ui->btn_biaozhunxianshuliang->setText(value);
		setConfig.biaozhunxianshuliang = value.toInt();
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
		ui->btn_zengyi->setText(value);
		setConfig.zengyi = value.toDouble();
	}
}