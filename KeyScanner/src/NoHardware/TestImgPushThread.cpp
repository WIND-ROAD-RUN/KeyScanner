#include"TestImgPushThread.hpp"

#include <QDir>

#include"GlobalStruct.hpp"
#include <random>

#ifdef BUILD_WITHOUT_HARDWARE
void TestImgPushThread::setPushImgTime(size_t pushImgTime)
{
	_pushImgTime = pushImgTime;
}

TestImgPushThread::TestImgPushThread(QObject* parent)
	: QThread(parent), _running(false) {
	readAllImgsPath();
}

TestImgPushThread::~TestImgPushThread()
{
	stopThread();
	wait();
}

void TestImgPushThread::readAllImgsPath()
{
	auto paths = globalPath.testImgDirPath;
	QDir dir(paths);
	if (!dir.exists()) {
		qDebug() << "Directory does not exist: " << paths;
		return;
	}
	static const QSet<QString> supportedSuffixes = {
		"jpg", "jpeg", "png", "bmp", "gif", "tiff", "webp"
	};
	QFileInfoList fileList = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot, QDir::Name);
	imgsPath.clear();
	imgCache.clear();
	int cacheCount = 0;
	for (const QFileInfo& fileInfo : fileList) {
		if (fileInfo.isFile() && supportedSuffixes.contains(fileInfo.suffix().toLower())) {
			imgsPath.append(fileInfo.absoluteFilePath());
			if (cacheCount < 100) {
				cv::Mat mat = cv::imread(fileInfo.absoluteFilePath().toStdString());
				if (!mat.empty()) {
					imgCache.append(mat);
					++cacheCount;
				}
			}
		}
	}
}

void TestImgPushThread::startThread()
{
	_running = true;
	if (!isRunning()) {
		start();
	}
}

void TestImgPushThread::stopThread()
{
	_running = false;
}

void TestImgPushThread::readImg(size_t s)
{
	auto& isPushImg = GlobalThread::getInstance().testImgPush;
	if (!isPushImg.load())
	{
		return;
	}

	if (s % _pushImgTime == 0 && !imgCache.isEmpty())
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, imgCache.size() - 1);

		int randomIndex = dis(gen);

		rw::rqw::MatInfo selectedImg{};

		selectedImg.mat = imgCache[randomIndex].clone();

		emit imgReady(selectedImg, 1);
	}
}

void TestImgPushThread::run()
{
	static size_t s = 0;
	while (_running) {
		QThread::msleep(1);
		++s;
		readImg(s);
		if (s == 1000000)
		{
			s = 0;
		}
	}
}
#endif



