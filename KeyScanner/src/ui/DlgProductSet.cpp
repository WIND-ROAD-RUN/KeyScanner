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
	ui->btn_chuiqishijian->setText(QString::number(setConfig.chuiqishijian));
	ui->btn_xiangsudangliang->setText(QString::number(setConfig.xiangsudangliang));
	ui->btn_jishuguangdianyanshi->setText(QString::number(setConfig.jishuguangdianyanshi));
	ui->btn_paizhaoyanshi->setText(QString::number(setConfig.paizhaoyanshi));
	ui->btn_tifeiyanshi->setText(QString::number(setConfig.tifeiyanshi));
	ui->btn_score->setText(QString::number(setConfig.score));
	ui->btn_cipinguangdianjiange->setText(QString::number(setConfig.cipinguangdianjiange));
	ui->btn_fenliaojishu->setText(QString::number(setConfig.fenliaojishu));
	ui->btn_xiangjiguangdianpingbishijian->setText(QString::number(setConfig.xiangjiguangdianpingbishijian));
	ui->btn_pidaiduibiyanse->setText(QString::number(setConfig.pidaiduibiyanse));

	// 相机参数
	ui->btn_shangxianwei->setText(QString::number(setConfig.shangxianwei));
	ui->btn_xiaxianwei->setText(QString::number(setConfig.xiaxianwei));
	ui->btn_baoguang->setText(QString::number(setConfig.baoguang));
	ui->btn_zengyi->setText(QString::number(setConfig.zengyi));

	ui->cbox_changeLanguage->setCurrentIndex(setConfig.changeLanguageIndex);
	changeLanguage(setConfig.changeLanguageIndex);
}

void DlgProductSet::build_connect()
{
	connect(ui->btn_close, &QPushButton::clicked, this, &DlgProductSet::btn_close_clicked);
	connect(ui->btn_chuiqishijian, &QPushButton::clicked, this, &DlgProductSet::btn_chuiqishijian_clicked);
	connect(ui->btn_xiangsudangliang, &QPushButton::clicked, this, &DlgProductSet::btn_xiangsudangliang_clicked);
	connect(ui->btn_jishuguangdianyanshi, &QPushButton::clicked, this, &DlgProductSet::btn_jishuguangdianyanshi_clicked);
	connect(ui->btn_paizhaoyanshi, &QPushButton::clicked, this, &DlgProductSet::btn_paizhaoyanshi_clicked);
	connect(ui->btn_tifeiyanshi, &QPushButton::clicked, this, &DlgProductSet::btn_tifeiyanshi_clicked);
	connect(ui->btn_score, &QPushButton::clicked, this, &DlgProductSet::btn_score_clicked);
	connect(ui->btn_cipinguangdianjiange, &QPushButton::clicked, this, &DlgProductSet::btn_cipinguangdianjiange_clicked);
	connect(ui->btn_fenliaojishu, &QPushButton::clicked, this, &DlgProductSet::btn_fenliaojishu_clicked);
	connect(ui->btn_xiangjiguangdianpingbishijian, &QPushButton::clicked, this, &DlgProductSet::btn_xiangjiguangdianpingbishijian_clicked);
	connect(ui->btn_pidaiduibiyanse, &QPushButton::clicked, this, &DlgProductSet::btn_pidaiduibiyanse_clicked);
	connect(ui->btn_shangxianwei, &QPushButton::clicked, this, &DlgProductSet::btn_shangxianwei_clicked);
	connect(ui->btn_xiaxianwei, &QPushButton::clicked, this, &DlgProductSet::btn_xiaxianwei_clicked);
	connect(ui->btn_baoguang, &QPushButton::clicked, this, &DlgProductSet::btn_baoguang_clicked);
	connect(ui->btn_zengyi, &QPushButton::clicked, this, &DlgProductSet::btn_zengyi_clicked);
	connect(ui->cbox_changeLanguage, &QComboBox::currentIndexChanged, this, &DlgProductSet::changeLanguage);
}

void DlgProductSet::changeLanguage(int index)
{
	// 中文
	if (0 == index)
	{
		ui->lb_chuiqishijian->setText("吹气时间");
		ui->lb_jishuguangdianyanshi->setText("计数光电延时");
		ui->lb_tifeiyanshi->setText("剔废延时");
		ui->lb_cipinguangdianjiange->setText("次品光电间隔");
		ui->lb_cipinguangdianjiangeUnit->setText("个");
		ui->lb_xiangjiguangdianpingbishijian->setText("相机光电屏蔽时间");
		ui->lb_xiangsudangliang->setText("像素当量");
		ui->lb_paizhaoyanshi->setText("拍照延时");
		ui->lb_shaixuanfenshu->setText("筛选分数");
		ui->lb_fenliaojishu->setText("分料计数");
		ui->lb_fenliaojishuUnit->setText("个");
		ui->lb_pidaiduibiyanse->setText("皮带对比颜色");

		ui->lb_shangxianwei->setText("上限位");
		ui->lb_xiaxianwei->setText("下限位");
		ui->lb_baoguang->setText("曝光");
		ui->lb_zengyi->setText("增益");
	}
	// 英文
	else if (1 == index)
	{
		ui->lb_chuiqishijian->setText("Blowing time");
		ui->lb_jishuguangdianyanshi->setText("Counting photoelectric delay");
		ui->lb_tifeiyanshi->setText("Rejection delay");
		ui->lb_cipinguangdianjiange->setText("Defective photoelectric interval");
		ui->lb_cipinguangdianjiangeUnit->setText("amount");
		ui->lb_xiangjiguangdianpingbishijian->setText("Camera photoelectric shielding time");
		ui->lb_xiangsudangliang->setText("Pixel equivalent");
		ui->lb_paizhaoyanshi->setText("Photo Delay");
		ui->lb_shaixuanfenshu->setText("Screening score");
		ui->lb_fenliaojishu->setText("Dosage counting");
		ui->lb_fenliaojishuUnit->setText("amount");
		ui->lb_pidaiduibiyanse->setText("Belt contrasting color");

		ui->lb_shangxianwei->setText("Upper limit");
		ui->lb_xiaxianwei->setText("Lower limit");
		ui->lb_baoguang->setText("exposure");
		ui->lb_zengyi->setText("gain");
	}
	auto& setConfig = GlobalData::getInstance().setConfig;
	setConfig.changeLanguageIndex = index;
	emit emit_changeLanguage(index);
}

void DlgProductSet::btn_close_clicked()
{
	auto& globalFunc = GlobalFuncObject::getInstance();

	globalFunc.saveSetConfig();
	emit paramsChanged();
	this->close();
}

void DlgProductSet::btn_chuiqishijian_clicked()
{
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的数值");
			return;
		}
		auto& setConfig = GlobalData::getInstance().setConfig;
		ui->btn_chuiqishijian->setText(value);
		setConfig.chuiqishijian = value.toDouble();
	}
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

void DlgProductSet::btn_jishuguangdianyanshi_clicked()
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
		ui->btn_jishuguangdianyanshi->setText(value);
		setConfig.jishuguangdianyanshi = value.toDouble();
	}
}

void DlgProductSet::btn_paizhaoyanshi_clicked()
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
		ui->btn_paizhaoyanshi->setText(value);
		setConfig.paizhaoyanshi = value.toDouble();
	}
}

void DlgProductSet::btn_tifeiyanshi_clicked()
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
		ui->btn_tifeiyanshi->setText(value);
		setConfig.tifeiyanshi = value.toDouble();
	}
}

void DlgProductSet::btn_score_clicked()
{
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0 || value.toDouble() > 100)
		{
			QMessageBox::warning(this, "提示", "请输入[0,100]]的数值");
			return;
		}
		auto& setConfig = GlobalData::getInstance().setConfig;
		ui->btn_score->setText(value);
		setConfig.score = value.toDouble();
	}
}

void DlgProductSet::btn_cipinguangdianjiange_clicked()
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
		ui->btn_cipinguangdianjiange->setText(value);
		setConfig.cipinguangdianjiange = value.toDouble();
	}
}

void DlgProductSet::btn_fenliaojishu_clicked()
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
		ui->btn_fenliaojishu->setText(value);
		setConfig.fenliaojishu = value.toDouble();
	}
}

void DlgProductSet::btn_xiangjiguangdianpingbishijian_clicked()
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
		ui->btn_xiangjiguangdianpingbishijian->setText(value);
		setConfig.xiangjiguangdianpingbishijian = value.toDouble();
	}
}

void DlgProductSet::btn_pidaiduibiyanse_clicked()
{
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的数值");
			return;
		}
		auto& setConfig = GlobalData::getInstance().setConfig;
		ui->btn_pidaiduibiyanse->setText(value);
		setConfig.pidaiduibiyanse = value.toDouble();
	}
}

void DlgProductSet::btn_shangxianwei_clicked()
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
		ui->btn_shangxianwei->setText(value);
		setConfig.shangxianwei = value.toDouble();
	}
}

void DlgProductSet::btn_xiaxianwei_clicked()
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
		ui->btn_xiaxianwei->setText(value);
		setConfig.xiaxianwei = value.toDouble();
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



