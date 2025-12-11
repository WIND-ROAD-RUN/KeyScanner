#include <QMessageBox>
#include <iostream>
#include <windows.h>
#include <QtWidgets/QApplication>
#include "KeyScanner.h"
#include "Utilty.hpp"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

	// 初始化控制台编码
	if (!Utility::initializeConsoleEncoding())
	{
		std::cerr << "Console encoding initialization failed, but continuing..." << std::endl;
	}

	// 设置 Qt 消息处理器
	Utility::setupQtMessageHandler();

	if (!KeyScanner::check())
	{
		return 1;
	}

    KeyScanner w;

#ifdef NDEBUG
	w.showFullScreen();
#else
	w.show();
#endif
    return a.exec();
}
