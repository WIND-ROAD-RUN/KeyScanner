#include "DetachCheckPlcController.h"
#include "GlobalStruct.hpp"

DetachCheckPlcController::DetachCheckPlcController(QObject* parent)
	: QThread(parent), running(false)
{
}

DetachCheckPlcController::~DetachCheckPlcController()
{
	stopThread();
	wait();
}

void DetachCheckPlcController::startThread()
{
	running = true;
	if (!isRunning()) {
		start();
	}
}

void DetachCheckPlcController::stopThread()
{
	running = false;
}

void DetachCheckPlcController::run()
{
	while (running) {
		QThread::msleep(1);
		listen();
	}
}

void DetachCheckPlcController::listen()
{
	auto plcControllerScheduler = GlobalThread::getInstance().plcController.plcControllerScheduler;
	auto isSuccess = plcControllerScheduler->readRegister32Async(700,
		rw::hoem::Endianness::LittleEndian,
		3, std::chrono::milliseconds(1000));

	plcControllerScheduler->wait();
	/*if (isSuccess.get())
	{
		emit getSignal();
	}*/
	emit getSignal();
}
