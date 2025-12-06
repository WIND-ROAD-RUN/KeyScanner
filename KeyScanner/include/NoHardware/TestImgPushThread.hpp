#pragma once

#include <QThread>
#include <atomic>
#include <opencv2/core/mat.hpp>

#include "rqw_CameraObjectCore.hpp"


#ifdef BUILD_WITHOUT_HARDWARE
class TestImgPushThread : public QThread
{
	Q_OBJECT
public:
	std::atomic_bool isProcessing{ false };
	std::atomic_bool isProcessFinish{ false };
private:
	QVector<QString> imgsPath{};
	QVector<cv::Mat> imgCache;
private:
	size_t _pushImgTime{ 150 };
public:
	void setPushImgTime(size_t pushImgTime);
public:
	explicit TestImgPushThread(QObject* parent = nullptr);

	~TestImgPushThread() override;
private:
	void readAllImgsPath();
public:
	void startThread();

	void stopThread();

signals:
	void imgReady(rw::rqw::MatInfo matInfo, size_t index);
public:
	void readImg(size_t s);
protected:
	void run() override;
private:
	std::atomic<bool> _running;
};
#endif

