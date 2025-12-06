#pragma once

#include <QDialog>
#include "ui_DlgLimit.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DlgLimitClass; };
QT_END_NAMESPACE

class DlgLimit : public QDialog
{
	Q_OBJECT

public:
	DlgLimit(QWidget *parent = nullptr);
	~DlgLimit();
public:
	void build_ui();
	void read_config();
	void build_connect();

private slots:
	void btn_close_clicked();

	void btn_neichi1zuoxiaxian_clicked();
	void btn_neichi2zuoxiaxian_clicked();
	void btn_neichi3zuoxiaxian_clicked();
	void btn_neichi4zuoxiaxian_clicked();
	void btn_neichi1zuoshangxian_clicked();
	void btn_neichi2zuoshangxian_clicked();
	void btn_neichi3zuoshangxian_clicked();
	void btn_neichi4zuoshangxian_clicked();

	void btn_neichi1youxiaxian_clicked();
	void btn_neichi2youxiaxian_clicked();
	void btn_neichi3youxiaxian_clicked();
	void btn_neichi4youxiaxian_clicked();
	void btn_neichi1youshangxian_clicked();
	void btn_neichi2youshangxian_clicked();
	void btn_neichi3youshangxian_clicked();
	void btn_neichi4youshangxian_clicked();

private:
	Ui::DlgLimitClass *ui;
};

