#include <QMessageBox>
#include <iostream>
#include <windows.h>
#include <QtWidgets/QApplication>
#include "KeyScanner.h"

extern bool initializeConsoleEncoding();

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

	// 初始化控制台编码
	if (!initializeConsoleEncoding())
	{
		std::cerr << "Console encoding initialization failed, but continuing..." << std::endl;
	}


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


// 初始化控制台编码为 UTF-8
bool initializeConsoleEncoding()
{
	bool success = true;

	// 设置控制台输出编码为 UTF-8
	if (!SetConsoleOutputCP(CP_UTF8))
	{
		std::cerr << "Warning: Failed to set console output code page to UTF-8" << std::endl;
		success = false;
	}

	// 设置控制台输入编码为 UTF-8
	if (!SetConsoleCP(CP_UTF8))
	{
		std::cerr << "Warning: Failed to set console input code page to UTF-8" << std::endl;
		success = false;
	}

	// 设置 C++ 流的编码
	if (success)
	{
		std::cout.imbue(std::locale(""));
		std::cerr.imbue(std::locale(""));
		std::clog.imbue(std::locale(""));
	}

	return success;
}
