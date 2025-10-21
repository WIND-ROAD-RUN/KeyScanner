#pragma once

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class DlgProductSetClass; };
QT_END_NAMESPACE

class DlgProductSet : public QDialog
{
	Q_OBJECT

public:
	DlgProductSet(QWidget* parent = nullptr);
	~DlgProductSet();

public:
	void build_ui();
	void read_config();
	void build_connect();

signals:
	void paramsChanged();

public slots:
private slots:
	void btn_close_clicked();

	void btn_xiangsudangliang_clicked();
	void btn_biaozhunxianjiange_clicked();
	void btn_biaozhunxianshangjuli_clicked();
	void btn_biaozhunxianshuliang_clicked();

	void btn_baoguang_clicked();
	void btn_zengyi_clicked();
private:
	Ui::DlgProductSetClass* ui;
};

