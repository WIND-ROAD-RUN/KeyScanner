#pragma once
#include <QThread>
#include <QDebug>
#include <atomic>

class DetachCheckPlcController : public QThread
{
	Q_OBJECT
public:
	explicit DetachCheckPlcController(QObject* parent = nullptr);

	~DetachCheckPlcController() override;

	void startThread();

	void stopThread();
protected:
	void run() override;
private:
	void listen();
signals:
	void getSignal();
private:
	std::atomic<bool> running; // 使用原子变量保证线程安全
};
