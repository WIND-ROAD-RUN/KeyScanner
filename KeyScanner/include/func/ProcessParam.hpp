#pragma once

#ifdef BUILD_WITH_HALCON

#include <QString>
#include <QMap>
#include <halconcpp/HalconCpp.h>

namespace rw {
namespace rqw {

/**
 * @brief Halcon 图像处理参数管理类
 * 
 * 用于存储和管理 Halcon 图像处理的各种参数，包括 ROI、阈值、形态学操作参数等
 */
class ProcessParam
{
public:
    // ROI 类型枚举
    enum class RoiType {
        Rectangle,      // 矩形
        Circle,         // 圆形
        Ellipse,        // 椭圆
        Polygon,        // 多边形
        Freehand        // 自由手绘
    };

    // 形态学操作类型
    enum class MorphologyType {
        Erosion,        // 腐蚀
        Dilation,       // 膨胀
        Opening,        // 开运算
        Closing,        // 闭运算
        TopHat,         // 顶帽
        BottomHat       // 底帽
    };

public:
    /**
     * @brief 构造函数
     */
    ProcessParam();

    /**
     * @brief 析构函数
     */
    ~ProcessParam();

    /**
     * @brief 禁止拷贝
     */
    ProcessParam(const ProcessParam&) = delete;
    ProcessParam& operator=(const ProcessParam&) = delete;

    /**
     * @brief 允许移动
     */
    ProcessParam(ProcessParam&& other) noexcept;
    ProcessParam& operator=(ProcessParam&& other) noexcept;

    // ==================== ROI 相关参数 ====================
    
    /**
     * @brief 设置 ROI 矩形参数
     * @param row1 左上角行坐标
     * @param col1 左上角列坐标
     * @param row2 右下角行坐标
     * @param col2 右下角列坐标
     */
    void setRoiRectangle(double row1, double col1, double row2, double col2);

    /**
     * @brief 获取 ROI 矩形参数
     */
    void getRoiRectangle(double& row1, double& col1, double& row2, double& col2) const;

    /**
     * @brief 设置 ROI 类型
     */
    void setRoiType(RoiType type) { _roiType = type; }

    /**
     * @brief 获取 ROI 类型
     */
    RoiType getRoiType() const { return _roiType; }

    /**
     * @brief 是否有 ROI
     */
    bool hasRoi() const { return _hasRoi; }

    /**
     * @brief 清除 ROI
     */
    void clearRoi();

    /**
     * @brief 生成 ROI 的 HObject
     * @return ROI 的 Halcon 对象
     */
    HalconCpp::HObject generateRoi() const;

    // ==================== 图像预处理参数 ====================

    /**
     * @brief 设置高斯滤波参数
     * @param sigma 高斯核标准差
     */
    void setGaussianSigma(double sigma) { _gaussianSigma = sigma; }

    /**
     * @brief 获取高斯滤波参数
     */
    double getGaussianSigma() const { return _gaussianSigma; }

    /**
     * @brief 设置中值滤波掩膜大小
     * @param maskSize 掩膜大小（奇数）
     */
    void setMedianMaskSize(int maskSize) { _medianMaskSize = maskSize; }

    /**
     * @brief 获取中值滤波掩膜大小
     */
    int getMedianMaskSize() const { return _medianMaskSize; }

    /**
     * @brief 设置均值滤波掩膜大小
     * @param maskSize 掩膜大小
     */
    void setMeanMaskSize(int maskSize) { _meanMaskSize = maskSize; }

    /**
     * @brief 获取均值滤波掩膜大小
     */
    int getMeanMaskSize() const { return _meanMaskSize; }

    // ==================== 阈值分割参数 ====================

    /**
     * @brief 设置阈值参数
     * @param minVal 最小阈值
     * @param maxVal 最大阈值
     */
    void setThreshold(double minVal, double maxVal);

    /**
     * @brief 获取阈值参数
     */
    void getThreshold(double& minVal, double& maxVal) const;

    /**
     * @brief 是否使用自动阈值
     */
    void setUseAutoThreshold(bool use) { _useAutoThreshold = use; }

    /**
     * @brief 获取是否使用自动阈值
     */
    bool getUseAutoThreshold() const { return _useAutoThreshold; }

    /**
     * @brief 设置自动阈值方法
     * @param method 方法名 (如 "max_separability", "smooth_histo" 等)
     */
    void setAutoThresholdMethod(const QString& method) { _autoThresholdMethod = method; }

    /**
     * @brief 获取自动阈值方法
     */
    QString getAutoThresholdMethod() const { return _autoThresholdMethod; }

    // ==================== 形态学操作参数 ====================

    /**
     * @brief 设置形态学操作类型
     */
    void setMorphologyType(MorphologyType type) { _morphologyType = type; }

    /**
     * @brief 获取形态学操作类型
     */
    MorphologyType getMorphologyType() const { return _morphologyType; }

    /**
     * @brief 设置形态学核大小
     * @param width 宽度
     * @param height 高度
     */
    void setMorphologyKernelSize(int width, int height);

    /**
     * @brief 获取形态学核大小
     */
    void getMorphologyKernelSize(int& width, int& height) const;

    /**
     * @brief 设置形态学迭代次数
     */
    void setMorphologyIterations(int iterations) { _morphologyIterations = iterations; }

    /**
     * @brief 获取形态学迭代次数
     */
    int getMorphologyIterations() const { return _morphologyIterations; }

    // ==================== 边缘检测参数 ====================

    /**
     * @brief 设置 Canny 边缘检测参数
     * @param low 低阈值
     * @param high 高阈值
     */
    void setCannyThresholds(double low, double high);

    /**
     * @brief 获取 Canny 边缘检测参数
     */
    void getCannyThresholds(double& low, double& high) const;

    /**
     * @brief 设置 Sobel 滤波器大小
     * @param size 滤波器大小 (如 3, 5, 7)
     */
    void setSobelSize(int size) { _sobelSize = size; }

    /**
     * @brief 获取 Sobel 滤波器大小
     */
    int getSobelSize() const { return _sobelSize; }

    // ==================== 测量参数 ====================

    /**
     * @brief 设置最小面积阈值
     * @param area 最小面积
     */
    void setMinArea(double area) { _minArea = area; }

    /**
     * @brief 获取最小面积阈值
     */
    double getMinArea() const { return _minArea; }

    /**
     * @brief 设置最大面积阈值
     * @param area 最大面积
     */
    void setMaxArea(double area) { _maxArea = area; }

    /**
     * @brief 获取最大面积阈值
     */
    double getMaxArea() const { return _maxArea; }

    /**
     * @brief 设置最小灰度值
     */
    void setMinGray(double gray) { _minGray = gray; }

    /**
     * @brief 获取最小灰度值
     */
    double getMinGray() const { return _minGray; }

    /**
     * @brief 设置最大灰度值
     */
    void setMaxGray(double gray) { _maxGray = gray; }

    /**
     * @brief 获取最大灰度值
     */
    double getMaxGray() const { return _maxGray; }

    // ==================== 其他参数 ====================

    /**
     * @brief 设置自定义参数
     * @param name 参数名
     * @param value 参数值
     */
    void setCustomParam(const QString& name, double value);

    /**
     * @brief 获取自定义参数
     * @param name 参数名
     * @param defaultValue 默认值
     * @return 参数值
     */
    double getCustomParam(const QString& name, double defaultValue = 0.0) const;

    /**
     * @brief 清除所有自定义参数
     */
    void clearCustomParams();

    /**
     * @brief 重置所有参数为默认值
     */
    void resetToDefaults();

    /**
     * @brief 从配置文件加载参数
     * @param filePath 配置文件路径
     * @return 是否加载成功
     */
    bool loadFromFile(const QString& filePath);

    /**
     * @brief 保存参数到配置文件
     * @param filePath 配置文件路径
     * @return 是否保存成功
     */
    bool saveToFile(const QString& filePath) const;

    /**
     * @brief 打印所有参数（用于调试）
     */
    void printParams() const;

private:
    // ROI 参数
    bool _hasRoi = false;
    RoiType _roiType = RoiType::Rectangle;
    double _roiRow1 = 0.0;
    double _roiCol1 = 0.0;
    double _roiRow2 = 0.0;
    double _roiCol2 = 0.0;

    // 预处理参数
    double _gaussianSigma = 1.0;        // 高斯滤波标准差
    int _medianMaskSize = 3;            // 中值滤波掩膜大小
    int _meanMaskSize = 3;              // 均值滤波掩膜大小

    // 阈值分割参数
    double _thresholdMin = 0.0;         // 最小阈值
    double _thresholdMax = 255.0;       // 最大阈值
    bool _useAutoThreshold = false;     // 是否使用自动阈值
    QString _autoThresholdMethod = "max_separability";  // 自动阈值方法

    // 形态学参数
    MorphologyType _morphologyType = MorphologyType::Opening;
    int _morphologyKernelWidth = 3;     // 形态学核宽度
    int _morphologyKernelHeight = 3;    // 形态学核高度
    int _morphologyIterations = 1;      // 形态学迭代次数

    // 边缘检测参数
    double _cannyLow = 50.0;            // Canny 低阈值
    double _cannyHigh = 150.0;          // Canny 高阈值
    int _sobelSize = 3;                 // Sobel 滤波器大小

    // 测量参数
    double _minArea = 100.0;            // 最小面积
    double _maxArea = 999999.0;         // 最大面积
    double _minGray = 0.0;              // 最小灰度
    double _maxGray = 255.0;            // 最大灰度

    // 自定义参数
    QMap<QString, double> _customParams;
};

} // namespace rqw
} // namespace rw

#endif // BUILD_WITH_HALCON
