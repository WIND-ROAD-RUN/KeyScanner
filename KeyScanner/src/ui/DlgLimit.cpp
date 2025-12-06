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
	ui->btn_neichi1zuoxiaxian->setText(QString::number(limitConfg.neichi1zuoxiaxian));
	ui->btn_neichi2zuoxiaxian->setText(QString::number(limitConfg.neichi2zuoxiaxian));
	ui->btn_neichi3zuoxiaxian->setText(QString::number(limitConfg.neichi3zuoxiaxian));
	ui->btn_neichi4zuoxiaxian->setText(QString::number(limitConfg.neichi4zuoxiaxian));
	ui->btn_neichi1zuoshangxian->setText(QString::number(limitConfg.neichi1zuoshangxian));
	ui->btn_neichi2zuoshangxian->setText(QString::number(limitConfg.neichi2zuoshangxian));
	ui->btn_neichi3zuoshangxian->setText(QString::number(limitConfg.neichi3zuoshangxian));
	ui->btn_neichi4zuoshangxian->setText(QString::number(limitConfg.neichi4zuoshangxian));

	ui->btn_neichi1youxiaxian->setText(QString::number(limitConfg.neichi1youxiaxian));
	ui->btn_neichi2youxiaxian->setText(QString::number(limitConfg.neichi2youxiaxian));
	ui->btn_neichi3youxiaxian->setText(QString::number(limitConfg.neichi3youxiaxian));
	ui->btn_neichi4youxiaxian->setText(QString::number(limitConfg.neichi4youxiaxian));
	ui->btn_neichi1youshangxian->setText(QString::number(limitConfg.neichi1youshangxian));
	ui->btn_neichi2youshangxian->setText(QString::number(limitConfg.neichi2youshangxian));
	ui->btn_neichi3youshangxian->setText(QString::number(limitConfg.neichi3youshangxian));
	ui->btn_neichi4youshangxian->setText(QString::number(limitConfg.neichi4youshangxian));
}

void DlgLimit::build_connect()
{
	connect(ui->btn_close, &QPushButton::clicked, this, &DlgLimit::btn_close_clicked);
	connect(ui->btn_neichi1zuoxiaxian, &QPushButton::clicked, this, &DlgLimit::btn_neichi1zuoxiaxian_clicked);
	connect(ui->btn_neichi2zuoxiaxian, &QPushButton::clicked, this, &DlgLimit::btn_neichi2zuoxiaxian_clicked);
	connect(ui->btn_neichi3zuoxiaxian, &QPushButton::clicked, this, &DlgLimit::btn_neichi3zuoxiaxian_clicked);
	connect(ui->btn_neichi4zuoxiaxian, &QPushButton::clicked, this, &DlgLimit::btn_neichi4zuoxiaxian_clicked);
	connect(ui->btn_neichi1zuoshangxian, &QPushButton::clicked, this, &DlgLimit::btn_neichi1zuoshangxian_clicked);
	connect(ui->btn_neichi2zuoshangxian, &QPushButton::clicked, this, &DlgLimit::btn_neichi2zuoshangxian_clicked);
	connect(ui->btn_neichi3zuoshangxian, &QPushButton::clicked, this, &DlgLimit::btn_neichi3zuoshangxian_clicked);
	connect(ui->btn_neichi4zuoshangxian, &QPushButton::clicked, this, &DlgLimit::btn_neichi4zuoshangxian_clicked);

	connect(ui->btn_neichi1youxiaxian, &QPushButton::clicked, this, &DlgLimit::btn_neichi1youxiaxian_clicked);
	connect(ui->btn_neichi2youxiaxian, &QPushButton::clicked, this, &DlgLimit::btn_neichi2youxiaxian_clicked);
	connect(ui->btn_neichi3youxiaxian, &QPushButton::clicked, this, &DlgLimit::btn_neichi3youxiaxian_clicked);
	connect(ui->btn_neichi4youxiaxian, &QPushButton::clicked, this, &DlgLimit::btn_neichi4youxiaxian_clicked);
	connect(ui->btn_neichi1youshangxian, &QPushButton::clicked, this, &DlgLimit::btn_neichi1youshangxian_clicked);
	connect(ui->btn_neichi2youshangxian, &QPushButton::clicked, this, &DlgLimit::btn_neichi2youshangxian_clicked);
	connect(ui->btn_neichi3youshangxian, &QPushButton::clicked, this, &DlgLimit::btn_neichi3youshangxian_clicked);
	connect(ui->btn_neichi4youshangxian, &QPushButton::clicked, this, &DlgLimit::btn_neichi4youshangxian_clicked);
}

void DlgLimit::btn_close_clicked()
{
	auto& globalFunc = GlobalFuncObject::getInstance();
	globalFunc.saveLimitConfig();

	this->close();
}

void DlgLimit::btn_neichi1zuoxiaxian_clicked()
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
		ui->btn_neichi1zuoxiaxian->setText(value);
		limitConfig.neichi1zuoxiaxian = value.toDouble();
	}
}

void DlgLimit::btn_neichi2zuoxiaxian_clicked()
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
		ui->btn_neichi2zuoxiaxian->setText(value);
		limitConfig.neichi2zuoxiaxian = value.toDouble();
	}
}

void DlgLimit::btn_neichi3zuoxiaxian_clicked()
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
		ui->btn_neichi3zuoxiaxian->setText(value);
		limitConfig.neichi3zuoxiaxian = value.toDouble();
	}
}

void DlgLimit::btn_neichi4zuoxiaxian_clicked()
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
		ui->btn_neichi4zuoxiaxian->setText(value);
		limitConfig.neichi4zuoxiaxian = value.toDouble();
	}
}

void DlgLimit::btn_neichi1zuoshangxian_clicked()
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
		ui->btn_neichi1zuoshangxian->setText(value);
		limitConfig.neichi1zuoshangxian = value.toDouble();
	}
}

void DlgLimit::btn_neichi2zuoshangxian_clicked()
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
		ui->btn_neichi2zuoshangxian->setText(value);
		limitConfig.neichi2zuoshangxian = value.toDouble();
	}
}

void DlgLimit::btn_neichi3zuoshangxian_clicked()
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
		ui->btn_neichi3zuoshangxian->setText(value);
		limitConfig.neichi3zuoshangxian = value.toDouble();
	}
}

void DlgLimit::btn_neichi4zuoshangxian_clicked()
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
		ui->btn_neichi4zuoshangxian->setText(value);
		limitConfig.neichi4zuoshangxian = value.toDouble();
	}
}

void DlgLimit::btn_neichi1youxiaxian_clicked()
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
		ui->btn_neichi1youxiaxian->setText(value);
		limitConfig.neichi1youxiaxian = value.toDouble();
	}
}

void DlgLimit::btn_neichi2youxiaxian_clicked()
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
		ui->btn_neichi2youxiaxian->setText(value);
		limitConfig.neichi2youxiaxian = value.toDouble();
	}
}

void DlgLimit::btn_neichi3youxiaxian_clicked()
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
		ui->btn_neichi3youxiaxian->setText(value);
		limitConfig.neichi3youxiaxian = value.toDouble();
	}
}

void DlgLimit::btn_neichi4youxiaxian_clicked()
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
		ui->btn_neichi4youxiaxian->setText(value);
		limitConfig.neichi4youxiaxian = value.toDouble();
	}
}

void DlgLimit::btn_neichi1youshangxian_clicked()
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
		ui->btn_neichi1youshangxian->setText(value);
		limitConfig.neichi1youshangxian = value.toDouble();
	}
}

void DlgLimit::btn_neichi2youshangxian_clicked()
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
		ui->btn_neichi2youshangxian->setText(value);
		limitConfig.neichi2youshangxian = value.toDouble();
	}
}

void DlgLimit::btn_neichi3youshangxian_clicked()
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
		ui->btn_neichi3youshangxian->setText(value);
		limitConfig.neichi3youshangxian = value.toDouble();
	}
}

void DlgLimit::btn_neichi4youshangxian_clicked()
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
		ui->btn_neichi4youshangxian->setText(value);
		limitConfig.neichi4youshangxian = value.toDouble();
	}
}

