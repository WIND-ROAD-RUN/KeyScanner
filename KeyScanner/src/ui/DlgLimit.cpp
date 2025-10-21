#include "DlgLimit.h"

#include <QMessageBox>

#include "GlobalStruct.hpp"
#include "NumberKeyboard.h"

DlgLimit::DlgLimit(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::DlgLimitClass())
{
	ui->setupUi(this);

	build_ui();

	build_connect();
}

DlgLimit::~DlgLimit()
{
	delete ui;
}

void DlgLimit::build_ui()
{
	read_config();
}

void DlgLimit::read_config()
{
	auto& limitConfg = GlobalData::getInstance().limitConfig;
	ui->btn_waichi1xiaxian->setText(QString::number(limitConfg.waichi1xiaxian));
	ui->btn_waichi2xiaxian->setText(QString::number(limitConfg.waichi2xiaxian));
	ui->btn_waichi3xiaxian->setText(QString::number(limitConfg.waichi3xiaxian));
	ui->btn_waichi4xiaxian->setText(QString::number(limitConfg.waichi4xiaxian));
	ui->btn_waichi1shangxian->setText(QString::number(limitConfg.waichi1shangxian));
	ui->btn_waichi2shangxian->setText(QString::number(limitConfg.waichi2shangxian));
	ui->btn_waichi3shangxian->setText(QString::number(limitConfg.waichi3shangxian));
	ui->btn_waichi4shangxian->setText(QString::number(limitConfg.waichi4shangxian));
}

void DlgLimit::build_connect()
{
	connect(ui->btn_close, &QPushButton::clicked, this, &DlgLimit::btn_close_clicked);
	connect(ui->btn_waichi1xiaxian, &QPushButton::clicked, this, &DlgLimit::btn_waichi1xiaxian_clicked);
	connect(ui->btn_waichi2xiaxian, &QPushButton::clicked, this, &DlgLimit::btn_waichi2xiaxian_clicked);
	connect(ui->btn_waichi3xiaxian, &QPushButton::clicked, this, &DlgLimit::btn_waichi3xiaxian_clicked);
	connect(ui->btn_waichi4xiaxian, &QPushButton::clicked, this, &DlgLimit::btn_waichi4xiaxian_clicked);
	connect(ui->btn_waichi1shangxian, &QPushButton::clicked, this, &DlgLimit::btn_waichi1shangxian_clicked);
	connect(ui->btn_waichi2shangxian, &QPushButton::clicked, this, &DlgLimit::btn_waichi2shangxian_clicked);
	connect(ui->btn_waichi3shangxian, &QPushButton::clicked, this, &DlgLimit::btn_waichi3shangxian_clicked);
	connect(ui->btn_waichi4shangxian, &QPushButton::clicked, this, &DlgLimit::btn_waichi4shangxian_clicked);
}

void DlgLimit::btn_close_clicked()
{
	auto& globalFunc = GlobalFuncObject::getInstance();
	globalFunc.saveLimitConfig();

	this->close();
}

void DlgLimit::btn_waichi1xiaxian_clicked()
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
		auto& limitConfig = GlobalData::getInstance().limitConfig;
		ui->btn_waichi1xiaxian->setText(value);
		limitConfig.waichi1xiaxian = value.toDouble();
	}
}

void DlgLimit::btn_waichi2xiaxian_clicked()
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
		auto& limitConfig = GlobalData::getInstance().limitConfig;
		ui->btn_waichi2xiaxian->setText(value);
		limitConfig.waichi2xiaxian = value.toDouble();
	}
}

void DlgLimit::btn_waichi3xiaxian_clicked()
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
		auto& limitConfig = GlobalData::getInstance().limitConfig;
		ui->btn_waichi3xiaxian->setText(value);
		limitConfig.waichi3xiaxian = value.toDouble();
	}
}

void DlgLimit::btn_waichi4xiaxian_clicked()
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
		auto& limitConfig = GlobalData::getInstance().limitConfig;
		ui->btn_waichi4xiaxian->setText(value);
		limitConfig.waichi4xiaxian = value.toDouble();
	}
}

void DlgLimit::btn_waichi1shangxian_clicked()
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
		auto& limitConfig = GlobalData::getInstance().limitConfig;
		ui->btn_waichi1shangxian->setText(value);
		limitConfig.waichi1shangxian = value.toDouble();
	}
}

void DlgLimit::btn_waichi2shangxian_clicked()
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
		auto& limitConfig = GlobalData::getInstance().limitConfig;
		ui->btn_waichi2shangxian->setText(value);
		limitConfig.waichi2shangxian = value.toDouble();
	}
}

void DlgLimit::btn_waichi3shangxian_clicked()
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
		auto& limitConfig = GlobalData::getInstance().limitConfig;
		ui->btn_waichi3shangxian->setText(value);
		limitConfig.waichi3shangxian = value.toDouble();
	}
}

void DlgLimit::btn_waichi4shangxian_clicked()
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
		auto& limitConfig = GlobalData::getInstance().limitConfig;
		ui->btn_waichi4shangxian->setText(value);
		limitConfig.waichi4shangxian = value.toDouble();
	}
}

