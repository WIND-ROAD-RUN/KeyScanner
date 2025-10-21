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

	void btn_waichi1xiaxian_clicked();
	void btn_waichi2xiaxian_clicked();
	void btn_waichi3xiaxian_clicked();
	void btn_waichi4xiaxian_clicked();
	void btn_waichi1shangxian_clicked();
	void btn_waichi2shangxian_clicked();
	void btn_waichi3shangxian_clicked();
	void btn_waichi4shangxian_clicked();

private:
	Ui::DlgLimitClass *ui;
};

