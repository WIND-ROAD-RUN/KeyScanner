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
		checkCoil();
	}
}

void DetachCheckPlcController::listen()
{
	auto plcControllerScheduler = GlobalThread::getInstance().plcController.plcControllerScheduler;
	if (!plcControllerScheduler)
	{
		return;
	}

	try
	{
		auto isSuccess = plcControllerScheduler->readCoilAsync(188,
			3, std::chrono::milliseconds(1000));

		plcControllerScheduler->waitAll();
		if (isSuccess.get().first)
		{
			emit getSignal();
			// 重置线圈状态为 false
			auto writeResult = plcControllerScheduler->writeCoilAsync(188, false,
				3, std::chrono::milliseconds(1000));
			writeResult.get();
		}
	}
	catch (const std::exception& e)
	{
		qWarning() << "PLC operation failed:" << e.what();
		auto plcController = GlobalThread::getInstance().plcController.plcController;
		auto isReconnect = plcController->reconnect();
		if (isReconnect)
		{
			qDebug() << "PLC重新连接成功";
		}
	}
}

void DetachCheckPlcController::checkCoil()
{
	auto plcControllerScheduler = GlobalThread::getInstance().plcController.plcControllerScheduler;
	if (plcControllerScheduler)
	{
		bool isChuFa = false;
		try
		{
			auto isSuccess = plcControllerScheduler->readCoilAsync(188, isChuFa);
			if (isChuFa && isSuccess.get().first)
			{
				std::cout << "线圈触发!" << std::endl;

				auto bcd = plcControllerScheduler->writeCoilAsync(188, false);
			}
		}
		catch (const std::exception& e)
		{
			qWarning() << "Coil rewrite failed:" << e.what();
		}
	}
}
