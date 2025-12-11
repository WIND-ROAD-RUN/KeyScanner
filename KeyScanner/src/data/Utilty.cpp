#include "Utilty.hpp"

#include <iostream>
#include <windows.h>
#include <QtGlobal>

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#include <QTextCodec>
#endif

QString Utility::cameraIp1 = "1";
QString Utility::zmotionIp = "192.168.0.11";

bool Utility::initializeConsoleEncoding()
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
		try
		{
			std::cout.imbue(std::locale(""));
			std::cerr.imbue(std::locale(""));
			std::clog.imbue(std::locale(""));
		}
		catch (const std::exception& e)
		{
			std::cerr << "Warning: Failed to set locale: " << e.what() << std::endl;
			success = false;
		}
	}

	return success;
}

void Utility::setupQtMessageHandler()
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
	// Qt 5: 设置文本编码为 UTF-8
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#endif

	// 安装自定义消息处理器
	qInstallMessageHandler([](QtMsgType type, const QMessageLogContext& context, const QString& msg) {
		QByteArray localMsg = msg.toUtf8();
		const char* file = context.file ? context.file : "";
		const char* function = context.function ? context.function : "";

		switch (type) {
		case QtDebugMsg:
			fprintf(stderr, "Debug: %s\n", localMsg.constData());
			break;
		case QtInfoMsg:
			fprintf(stderr, "Info: %s\n", localMsg.constData());
			break;
		case QtWarningMsg:
			fprintf(stderr, "Warning: %s\n", localMsg.constData());
			break;
		case QtCriticalMsg:
			fprintf(stderr, "Critical: %s\n", localMsg.constData());
			break;
		case QtFatalMsg:
			fprintf(stderr, "Fatal: %s\n", localMsg.constData());
			abort();
		}
		});
}
