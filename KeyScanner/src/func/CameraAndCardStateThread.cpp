#include "CameraAndCardStateThread.h"

#include "GlobalStruct.hpp"

size_t CameraAndCardStateThread::runtimeCounts = 0;

CameraAndCardStateThread::CameraAndCardStateThread(QObject* parent)
	: QThread(parent), running(false), _dlgProductSet(GlobalData::getInstance().setConfig) {
}

CameraAndCardStateThread::~CameraAndCardStateThread()
{
	stopThread();
	wait();
}

void CameraAndCardStateThread::startThread()
{
	running = true;
	if (!isRunning()) {
		start();
	}
}

void CameraAndCardStateThread::stopThread()
{
	running = false;
}

void CameraAndCardStateThread::run()
{
	while (running) {
		QThread::msleep(2000);

		check_cameraState();
		check_cardState();

		runtimeCounts++;
		if (runtimeCounts == 4) {
			runtimeCounts = 0;
		}
	}
}

void CameraAndCardStateThread::check_cameraState()
{
	check_cameraState1();
}

void CameraAndCardStateThread::check_cameraState1()
{
	static bool isUpdateState = false;

	auto& globalThread = GlobalThread::getInstance();

	if (runtimeCounts != 0) {
		return;
	}
	if (globalThread.camera1) {
		if (globalThread.camera1->getConnectState()) {
			if (!isUpdateState) {
				emit updateCameraLabelState(1, true);
				isUpdateState = true;
			}
		}
		else {
			emit destroyCamera1();
			emit updateCameraLabelState(1, false);
		}
	}
	else {
		emit buildCamera1();
		emit updateCameraLabelState(1, false);
		isUpdateState = false;
	}
}

void CameraAndCardStateThread::check_cardState()
{
	static bool isUpdateState = false;

	auto& globalThread = GlobalThread::getInstance();

	if (runtimeCounts != 0) {
		return;
	}

	if (globalThread.zmotion) {
		if (globalThread.zmotion->getConnectState()) {
			if (!isUpdateState) {
				emit updateCameraLabelState(0, true);
				isUpdateState = true;
			}
		}
		else {
			emit destroyZMotion();
			emit updateCameraLabelState(0, false);
		}
	}
	else {
		emit buildZMotion();
		emit updateCameraLabelState(0, false);
		isUpdateState = false;
	}
}
