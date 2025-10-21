#pragma once
#include <QThread>
#include <QDebug>
#include <atomic>
#include "SetConfig.hpp"

class CameraAndCardStateThread : public QThread
{
	Q_OBJECT
private:
	static size_t runtimeCounts;

public:
	explicit CameraAndCardStateThread(QObject* parent = nullptr);

	~CameraAndCardStateThread() override;

	void startThread();

	void stopThread();

	cdm::SetConfig& _dlgProductSet;

protected:
	void run() override;
private:
	void check_cameraState();
	void check_cameraState1();

	void check_cardState();
signals:
	void updateCameraLabelState(int cameraIndex, bool state);
	void updateCardLabelState(bool state);
	void addWarningInfo(QString message, bool updateTimestampIfSame, int redDuration);

signals:
	void buildCamera1();
	void destroyCamera1();
	void startMonitor1();

	void buildZMotion();
	void destroyZMotion();
private:
	std::atomic<bool> running; // 使用原子变量保证线程安全
};