#include "ProcessParam.hpp"

#ifdef BUILD_WITH_HALCON

#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace rw {
namespace rqw {

ProcessParam::ProcessParam()
{
    resetToDefaults();
}

ProcessParam::~ProcessParam() = default;

ProcessParam::ProcessParam(ProcessParam&& other) noexcept
    : _hasRoi(other._hasRoi)
    , _roiType(other._roiType)
    , _roiRow1(other._roiRow1)
    , _roiCol1(other._roiCol1)
    , _roiRow2(other._roiRow2)
    , _roiCol2(other._roiCol2)
    , _gaussianSigma(other._gaussianSigma)
    , _medianMaskSize(other._medianMaskSize)
    , _meanMaskSize(other._meanMaskSize)
    , _thresholdMin(other._thresholdMin)
    , _thresholdMax(other._thresholdMax)
    , _useAutoThreshold(other._useAutoThreshold)
    , _autoThresholdMethod(std::move(other._autoThresholdMethod))
    , _morphologyType(other._morphologyType)
    , _morphologyKernelWidth(other._morphologyKernelWidth)
    , _morphologyKernelHeight(other._morphologyKernelHeight)
    , _morphologyIterations(other._morphologyIterations)
    , _cannyLow(other._cannyLow)
    , _cannyHigh(other._cannyHigh)
    , _sobelSize(other._sobelSize)
    , _minArea(other._minArea)
    , _maxArea(other._maxArea)
    , _minGray(other._minGray)
    , _maxGray(other._maxGray)
    , _customParams(std::move(other._customParams))
{
}

ProcessParam& ProcessParam::operator=(ProcessParam&& other) noexcept
{
    if (this != &other) {
        _hasRoi = other._hasRoi;
        _roiType = other._roiType;
        _roiRow1 = other._roiRow1;
        _roiCol1 = other._roiCol1;
        _roiRow2 = other._roiRow2;
        _roiCol2 = other._roiCol2;
        _gaussianSigma = other._gaussianSigma;
        _medianMaskSize = other._medianMaskSize;
        _meanMaskSize = other._meanMaskSize;
        _thresholdMin = other._thresholdMin;
        _thresholdMax = other._thresholdMax;
        _useAutoThreshold = other._useAutoThreshold;
        _autoThresholdMethod = std::move(other._autoThresholdMethod);
        _morphologyType = other._morphologyType;
        _morphologyKernelWidth = other._morphologyKernelWidth;
        _morphologyKernelHeight = other._morphologyKernelHeight;
        _morphologyIterations = other._morphologyIterations;
        _cannyLow = other._cannyLow;
        _cannyHigh = other._cannyHigh;
        _sobelSize = other._sobelSize;
        _minArea = other._minArea;
        _maxArea = other._maxArea;
        _minGray = other._minGray;
        _maxGray = other._maxGray;
        _customParams = std::move(other._customParams);
    }
    return *this;
}

// ==================== ROI 相关 ====================

void ProcessParam::setRoiRectangle(double row1, double col1, double row2, double col2)
{
    _roiType = RoiType::Rectangle;
    _roiRow1 = row1;
    _roiCol1 = col1;
    _roiRow2 = row2;
    _roiCol2 = col2;
    _hasRoi = true;
}

void ProcessParam::getRoiRectangle(double& row1, double& col1, double& row2, double& col2) const
{
    row1 = _roiRow1;
    col1 = _roiCol1;
    row2 = _roiRow2;
    col2 = _roiCol2;
}

void ProcessParam::clearRoi()
{
    _hasRoi = false;
    _roiRow1 = 0.0;
    _roiCol1 = 0.0;
    _roiRow2 = 0.0;
    _roiCol2 = 0.0;
}

HalconCpp::HObject ProcessParam::generateRoi() const
{
    using namespace HalconCpp;
    
    HObject hoRoi;
    
    if (!_hasRoi) {
        // 如果没有 ROI，返回全图
        GenRectangle1(&hoRoi, 0, 0, 1000, 1000);
        return hoRoi;
    }
    
    switch (_roiType) {
        case RoiType::Rectangle:
            GenRectangle1(&hoRoi, _roiRow1, _roiCol1, _roiRow2, _roiCol2);
            break;
        case RoiType::Circle:
            // 简化处理：用外接矩形代替
            GenRectangle1(&hoRoi, _roiRow1, _roiCol1, _roiRow2, _roiCol2);
            break;
        case RoiType::Ellipse:
            // 简化处理：用外接矩形代替
            GenRectangle1(&hoRoi, _roiRow1, _roiCol1, _roiRow2, _roiCol2);
            break;
        default:
            GenRectangle1(&hoRoi, _roiRow1, _roiCol1, _roiRow2, _roiCol2);
            break;
    }
    
    return hoRoi;
}

// ==================== 阈值分割 ====================

void ProcessParam::setThreshold(double minVal, double maxVal)
{
    _thresholdMin = minVal;
    _thresholdMax = maxVal;
    _useAutoThreshold = false;
}

void ProcessParam::getThreshold(double& minVal, double& maxVal) const
{
    minVal = _thresholdMin;
    maxVal = _thresholdMax;
}

// ==================== 形态学操作 ====================

void ProcessParam::setMorphologyKernelSize(int width, int height)
{
    _morphologyKernelWidth = width;
    _morphologyKernelHeight = height;
}

void ProcessParam::getMorphologyKernelSize(int& width, int& height) const
{
    width = _morphologyKernelWidth;
    height = _morphologyKernelHeight;
}

// ==================== 边缘检测 ====================

void ProcessParam::setCannyThresholds(double low, double high)
{
    _cannyLow = low;
    _cannyHigh = high;
}

void ProcessParam::getCannyThresholds(double& low, double& high) const
{
    low = _cannyLow;
    high = _cannyHigh;
}

// ==================== 自定义参数 ====================

void ProcessParam::setCustomParam(const QString& name, double value)
{
    _customParams[name] = value;
}

double ProcessParam::getCustomParam(const QString& name, double defaultValue) const
{
    auto it = _customParams.find(name);
    if (it != _customParams.end()) {
        return it.value();
    }
    return defaultValue;
}

void ProcessParam::clearCustomParams()
{
    _customParams.clear();
}

// ==================== 配置管理 ====================

void ProcessParam::resetToDefaults()
{
    _hasRoi = false;
    _roiType = RoiType::Rectangle;
    _roiRow1 = 0.0;
    _roiCol1 = 0.0;
    _roiRow2 = 0.0;
    _roiCol2 = 0.0;

    _gaussianSigma = 1.0;
    _medianMaskSize = 3;
    _meanMaskSize = 3;

    _thresholdMin = 0.0;
    _thresholdMax = 255.0;
    _useAutoThreshold = false;
    _autoThresholdMethod = "max_separability";

    _morphologyType = MorphologyType::Opening;
    _morphologyKernelWidth = 3;
    _morphologyKernelHeight = 3;
    _morphologyIterations = 1;

    _cannyLow = 50.0;
    _cannyHigh = 150.0;
    _sobelSize = 3;

    _minArea = 100.0;
    _maxArea = 999999.0;
    _minGray = 0.0;
    _maxGray = 255.0;

    _customParams.clear();
}

bool ProcessParam::loadFromFile(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "ProcessParam: 无法打开文件" << filePath;
        return false;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    
    if (doc.isNull() || !doc.isObject()) {
        qWarning() << "ProcessParam: JSON 解析失败";
        return false;
    }

    QJsonObject obj = doc.object();

    // 加载 ROI 参数
    if (obj.contains("roi")) {
        QJsonObject roiObj = obj["roi"].toObject();
        _hasRoi = roiObj["hasRoi"].toBool();
        _roiType = static_cast<RoiType>(roiObj["type"].toInt(0));
        _roiRow1 = roiObj["row1"].toDouble();
        _roiCol1 = roiObj["col1"].toDouble();
        _roiRow2 = roiObj["row2"].toDouble();
        _roiCol2 = roiObj["col2"].toDouble();
    }

    // 加载预处理参数
    if (obj.contains("preprocess")) {
        QJsonObject preObj = obj["preprocess"].toObject();
        _gaussianSigma = preObj["gaussianSigma"].toDouble(1.0);
        _medianMaskSize = preObj["medianMaskSize"].toInt(3);
        _meanMaskSize = preObj["meanMaskSize"].toInt(3);
    }

    // 加载阈值参数
    if (obj.contains("threshold")) {
        QJsonObject threshObj = obj["threshold"].toObject();
        _thresholdMin = threshObj["min"].toDouble(0.0);
        _thresholdMax = threshObj["max"].toDouble(255.0);
        _useAutoThreshold = threshObj["auto"].toBool(false);
        _autoThresholdMethod = threshObj["method"].toString("max_separability");
    }

    // 加载形态学参数
    if (obj.contains("morphology")) {
        QJsonObject morphObj = obj["morphology"].toObject();
        _morphologyType = static_cast<MorphologyType>(morphObj["type"].toInt(2));
        _morphologyKernelWidth = morphObj["kernelWidth"].toInt(3);
        _morphologyKernelHeight = morphObj["kernelHeight"].toInt(3);
        _morphologyIterations = morphObj["iterations"].toInt(1);
    }

    // 加载边缘检测参数
    if (obj.contains("edge")) {
        QJsonObject edgeObj = obj["edge"].toObject();
        _cannyLow = edgeObj["cannyLow"].toDouble(50.0);
        _cannyHigh = edgeObj["cannyHigh"].toDouble(150.0);
        _sobelSize = edgeObj["sobelSize"].toInt(3);
    }

    // 加载测量参数
    if (obj.contains("measure")) {
        QJsonObject measureObj = obj["measure"].toObject();
        _minArea = measureObj["minArea"].toDouble(100.0);
        _maxArea = measureObj["maxArea"].toDouble(999999.0);
        _minGray = measureObj["minGray"].toDouble(0.0);
        _maxGray = measureObj["maxGray"].toDouble(255.0);
    }

    // 加载自定义参数
    if (obj.contains("custom")) {
        QJsonObject customObj = obj["custom"].toObject();
        for (auto it = customObj.begin(); it != customObj.end(); ++it) {
            _customParams[it.key()] = it.value().toDouble();
        }
    }

    qDebug() << "ProcessParam: 参数已从" << filePath << "加载";
    return true;
}

bool ProcessParam::saveToFile(const QString& filePath) const
{
    QJsonObject obj;

    // 保存 ROI 参数
    QJsonObject roiObj;
    roiObj["hasRoi"] = _hasRoi;
    roiObj["type"] = static_cast<int>(_roiType);
    roiObj["row1"] = _roiRow1;
    roiObj["col1"] = _roiCol1;
    roiObj["row2"] = _roiRow2;
    roiObj["col2"] = _roiCol2;
    obj["roi"] = roiObj;

    // 保存预处理参数
    QJsonObject preObj;
    preObj["gaussianSigma"] = _gaussianSigma;
    preObj["medianMaskSize"] = _medianMaskSize;
    preObj["meanMaskSize"] = _meanMaskSize;
    obj["preprocess"] = preObj;

    // 保存阈值参数
    QJsonObject threshObj;
    threshObj["min"] = _thresholdMin;
    threshObj["max"] = _thresholdMax;
    threshObj["auto"] = _useAutoThreshold;
    threshObj["method"] = _autoThresholdMethod;
    obj["threshold"] = threshObj;

    // 保存形态学参数
    QJsonObject morphObj;
    morphObj["type"] = static_cast<int>(_morphologyType);
    morphObj["kernelWidth"] = _morphologyKernelWidth;
    morphObj["kernelHeight"] = _morphologyKernelHeight;
    morphObj["iterations"] = _morphologyIterations;
    obj["morphology"] = morphObj;

    // 保存边缘检测参数
    QJsonObject edgeObj;
    edgeObj["cannyLow"] = _cannyLow;
    edgeObj["cannyHigh"] = _cannyHigh;
    edgeObj["sobelSize"] = _sobelSize;
    obj["edge"] = edgeObj;

    // 保存测量参数
    QJsonObject measureObj;
    measureObj["minArea"] = _minArea;
    measureObj["maxArea"] = _maxArea;
    measureObj["minGray"] = _minGray;
    measureObj["maxGray"] = _maxGray;
    obj["measure"] = measureObj;

    // 保存自定义参数
    QJsonObject customObj;
    for (auto it = _customParams.begin(); it != _customParams.end(); ++it) {
        customObj[it.key()] = it.value();
    }
    obj["custom"] = customObj;

    QJsonDocument doc(obj);
    
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "ProcessParam: 无法写入文件" << filePath;
        return false;
    }

    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();

    qDebug() << "ProcessParam: 参数已保存到" << filePath;
    return true;
}

void ProcessParam::printParams() const
{
    qDebug() << "========== ProcessParam 参数 ==========";
    qDebug() << "ROI:";
    qDebug() << "  类型:" << static_cast<int>(_roiType);
    qDebug() << "  启用:" << _hasRoi;
    qDebug() << "  矩形:" << _roiRow1 << _roiCol1 << _roiRow2 << _roiCol2;
    
    qDebug() << "预处理:";
    qDebug() << "  高斯Sigma:" << _gaussianSigma;
    qDebug() << "  中值掩膜:" << _medianMaskSize;
    qDebug() << "  均值掩膜:" << _meanMaskSize;
    
    qDebug() << "阈值:";
    qDebug() << "  范围:" << _thresholdMin << "-" << _thresholdMax;
    qDebug() << "  自动阈值:" << _useAutoThreshold;
    qDebug() << "  方法:" << _autoThresholdMethod;
    
    qDebug() << "形态学:";
    qDebug() << "  类型:" << static_cast<int>(_morphologyType);
    qDebug() << "  核大小:" << _morphologyKernelWidth << "x" << _morphologyKernelHeight;
    qDebug() << "  迭代次数:" << _morphologyIterations;
    
    qDebug() << "边缘检测:";
    qDebug() << "  Canny阈值:" << _cannyLow << "-" << _cannyHigh;
    qDebug() << "  Sobel大小:" << _sobelSize;
    
    qDebug() << "测量:";
    qDebug() << "  面积范围:" << _minArea << "-" << _maxArea;
    qDebug() << "  灰度范围:" << _minGray << "-" << _maxGray;
    
    qDebug() << "自定义参数数量:" << _customParams.size();
    qDebug() << "=======================================";
}

} // namespace rqw
} // namespace rw

#endif // BUILD_WITH_HALCON
