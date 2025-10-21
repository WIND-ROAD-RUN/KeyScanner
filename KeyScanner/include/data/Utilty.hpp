#pragma once
#include <QString>

inline struct GlobalPath
{
public:
	QString projectHome = R"(D:\zfkjData\KeyScanner\)";
public:
	QString configRootPath = projectHome + R"(config\)";
	QString modelRootPath = projectHome + R"(model\)";
	QString qiXinShiJinDanXiangJiConfigPath = configRootPath + R"(KeyScannerConfig.xml)";
	QString setConfigPath = configRootPath + R"(SetConfig.xml)";
	QString limitConfigPath = configRootPath + R"(LimitConfig.xml)";
	QString modelPath = modelRootPath + R"(KeyScanner.engine)";

	QString testImgDirPath = R"(D:\zfkjDevelopment\ImgStorage\KeyScanner)";
}globalPath;


struct ClassId
{
public:
	static constexpr int Body = 0;
	static constexpr int Chi = 1;

	static constexpr int min = 0;
	static constexpr int max = 1;
	static constexpr int num = 2;
};

struct Utility
{
	static QString cameraIp1;
	static QString zmotionIp;
};

