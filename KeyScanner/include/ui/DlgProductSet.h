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

	void emit_changeLanguage(int index);
public slots:
	void changeLanguage(int index);
private slots:
	void btn_close_clicked();

	void btn_chuiqishijian_clicked();
	void btn_xiangsudangliang_clicked();
	void btn_jishuguangdianyanshi_clicked();
	void btn_paizhaoyanshi_clicked();
	void btn_tifeiyanshi_clicked();
	void btn_score_clicked();
	void btn_cipinguangdianjiange_clicked();
	void btn_fenliaojishu_clicked();
	void btn_xiangjiguangdianpingbishijian_clicked();
	void btn_pidaiduibiyanse_clicked();

	void btn_shangxianwei_clicked();
	void btn_xiaxianwei_clicked();
	void btn_baoguang_clicked();
	void btn_zengyi_clicked();
private:
	Ui::DlgProductSetClass* ui;
};

