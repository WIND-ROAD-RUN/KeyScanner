#include "DetachDefectThread.h"
#include "GlobalStruct.hpp"
#include <chrono>

DetachDefectThread::DetachDefectThread(QObject* parent)
{

}

DetachDefectThread::~DetachDefectThread()
{
	stopThread();
	wait(); // 等待线程安全退出
}

void DetachDefectThread::startThread()
{
	running = true;
	if (!isRunning()) {
		start(); // 启动线程
	}
}

void DetachDefectThread::stopThread()
{
	running = false; // 停止线程
}

void DetachDefectThread::processQueue(std::unique_ptr<rw::dsl::ThreadSafeHeap<bool>>& queue)
{
#ifdef BUILD_WITHOUT_HARDWARE
	// 记录开始时间
	auto start = std::chrono::high_resolution_clock::now();
#endif

	try
	{
		auto isBad = false;
		queue->tryGetTop(isBad);

		if (isBad)
		{
			
		}
	}
	catch (const std::runtime_error&)
	{
		#ifdef BUILD_WITHOUT_HARDWARE
		// 记录结束时间并打印耗时（毫秒）
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		std::cout << "[processQueue] WasteTime: " << duration << " mm" << std::endl;
		#endif

		return;
	}
	#ifdef BUILD_WITHOUT_HARDWARE
	// 记录结束时间并打印耗时（毫秒）
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::cout << "[processQueue] WasteTime: " << duration << " mm" << std::endl;
	#endif
}

void DetachDefectThread::run()
{
	auto& globalThread = GlobalThread::getInstance();
	auto& priorityQueue = globalThread.priorityQueue;

	while (running) {
		QThread::msleep(1);

		processQueue(priorityQueue);
	}
}
