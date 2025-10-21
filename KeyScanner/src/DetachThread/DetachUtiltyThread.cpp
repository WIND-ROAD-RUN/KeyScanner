#include"DetachUtiltyThread.h"

#include"GlobalStruct.hpp"

DetachUtiltyThread::DetachUtiltyThread(QObject* parent)
	: QThread(parent), running(false) {
}

DetachUtiltyThread::~DetachUtiltyThread()
{
	stopThread();
	wait(); // 等待线程安全退出
}

void DetachUtiltyThread::startThread()
{
	running = true;
	if (!isRunning()) {
		start(); // 启动线程
	}
}

void DetachUtiltyThread::stopThread()
{
	running = false; // 停止线程
}

void DetachUtiltyThread::run()
{
	static size_t s = 0;
	while (running) {
		QThread::sleep(1);
		CalculateBagInfos(s);
		++s;
		if (s == 300)
		{
			s = 0;
		}
	}
}

void DetachUtiltyThread::CalculateBagInfos(size_t s)
{
	auto& statisticalInfo = GlobalData::getInstance().statisticalInfo;

	emit updateStatisticalInfo();
}