#include "HalconDisplay.hpp"

#ifdef BUILD_WITH_HALCON

#include <QDebug>
#include <QString>
#include <halconcpp/HalconCpp.h>

namespace rw {
namespace rqw {

HalconDisplay::HalconDisplay(QWidget* parentWidget)
    : _parentWidget(parentWidget)
{
}

HalconDisplay::~HalconDisplay()
{
    closeWindow();
}

HalconDisplay::HalconDisplay(HalconDisplay&& other) noexcept
    : _parentWidget(other._parentWidget)
    , _windowHandle(other._windowHandle)
    , _lastImage(other._lastImage)
    , _isInitialized(other._isInitialized)
{
    other._parentWidget = nullptr;
    other._windowHandle = nullptr;
    other._lastImage = nullptr;
    other._isInitialized = false;
}

HalconDisplay& HalconDisplay::operator=(HalconDisplay&& other) noexcept
{
    if (this != &other) {
        closeWindow();
        
        _parentWidget = other._parentWidget;
        _windowHandle = other._windowHandle;
        _lastImage = other._lastImage;
        _isInitialized = other._isInitialized;
        
        other._parentWidget = nullptr;
        other._windowHandle = nullptr;
        other._lastImage = nullptr;
        other._isInitialized = false;
    }
    return *this;
}

bool HalconDisplay::initialize()
{
    if (!_parentWidget) {
        qWarning() << "HalconDisplay: 父控件为空，无法初始化";
        return false;
    }

    // 如果已经初始化，先关闭
    if (_isInitialized) {
        closeWindow();
    }

    try {
        using namespace HalconCpp;

        // 获取父控件的窗口句柄
        HWND hwnd = reinterpret_cast<HWND>(_parentWidget->winId());
        
        // 创建 Halcon 窗口句柄
        if (!_windowHandle) {
            _windowHandle = new HTuple();
        }

        // 创建 Halcon 窗口
        HTuple hvFatherWindow(reinterpret_cast<Hlong>(hwnd));
        OpenWindow(0, 0, 
            _parentWidget->width(), 
            _parentWidget->height(), 
            hvFatherWindow, "visible", "", _windowHandle);

        _isInitialized = true;
        qDebug() << "HalconDisplay: 窗口初始化成功，大小:" 
                 << _parentWidget->width() << "x" << _parentWidget->height();
        return true;
    }
    catch (const HalconCpp::HException& e) {
        qWarning() << "HalconDisplay 初始化错误:" << e.ErrorMessage().Text();
        return false;
    }
    catch (...) {
        qWarning() << "HalconDisplay: 初始化时发生未知错误";
        return false;
    }
}

void HalconDisplay::closeWindow()
{
    try {
        if (_windowHandle && _windowHandle->TupleLength() > 0) {
            HalconCpp::CloseWindow(*_windowHandle);
        }
    }
    catch (...) {
        // 忽略关闭窗口时的错误
    }

    delete _windowHandle;
    _windowHandle = nullptr;

    delete _lastImage;
    _lastImage = nullptr;

    _isInitialized = false;
}

bool HalconDisplay::isValid() const
{
    return _isInitialized && _windowHandle && _windowHandle->TupleLength() > 0;
}

bool HalconDisplay::displayImage(const HalconCpp::HObject& image, bool fitToWindow)
{
    if (!isValid()) {
        qWarning() << "HalconDisplay: 窗口未初始化，无法显示图片";
        return false;
    }

    try {
        using namespace HalconCpp;

        // 获取图片尺寸
        HTuple hvWidth, hvHeight;
        GetImageSize(image, &hvWidth, &hvHeight);

        // 如果需要自适应窗口大小，设置显示区域
        if (fitToWindow) {
            SetPart(*_windowHandle, 0, 0, hvHeight - 1, hvWidth - 1);
        }

        // 显示图片
        DispObj(image, *_windowHandle);

        // 保存图片引用
        if (_lastImage) {
            delete _lastImage;
        }
        _lastImage = new HObject(image);

        return true;
    }
    catch (const HalconCpp::HException& e) {
        qWarning() << "HalconDisplay 显示错误:" << e.ErrorMessage().Text();
        return false;
    }
    catch (...) {
        qWarning() << "HalconDisplay: 显示图片时发生未知错误";
        return false;
    }
}

bool HalconDisplay::displayImageFromFile(const QString& imagePath, bool fitToWindow)
{
    try {
        using namespace HalconCpp;

        // 读取图片
        HObject hoImage;
        ReadImage(&hoImage, imagePath.toStdString().c_str());

        // 显示图片
        return displayImage(hoImage, fitToWindow);
    }
    catch (const HalconCpp::HException& e) {
        qWarning() << "HalconDisplay 读取图片错误:" << e.ErrorMessage().Text();
        return false;
    }
    catch (...) {
        qWarning() << "HalconDisplay: 读取图片时发生未知错误";
        return false;
    }
}

void HalconDisplay::clearDisplay()
{
    if (!isValid()) {
        return;
    }

    try {
        HalconCpp::ClearWindow(*_windowHandle);
    }
    catch (...) {
        // 忽略清空时的错误
    }
}

void HalconDisplay::setDisplayPart(int row1, int col1, int row2, int col2)
{
    if (!isValid()) {
        return;
    }

    try {
        HalconCpp::SetPart(*_windowHandle, row1, col1, row2, col2);
    }
    catch (...) {
        // 忽略设置区域时的错误
    }
}

void HalconDisplay::resetDisplayPart(int imageWidth, int imageHeight)
{
    setDisplayPart(0, 0, imageHeight - 1, imageWidth - 1);
}

} // namespace rqw
} // namespace rw

#endif // BUILD_WITH_HALCON
