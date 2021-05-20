#pragma once

#include "../BaseWindow.h"
#include <d2d1.h>
#include <wrl.h>
#pragma comment(lib, "d2d1")

using namespace Microsoft::WRL;

class CircleWindow : public BaseWindow
{
    ComPtr<ID2D1Factory> pFactory;
    ComPtr<ID2D1HwndRenderTarget> pRenderTarget;
    ComPtr<ID2D1SolidColorBrush> pBrush;
    D2D1_ELLIPSE ellipse;

    void    CalculateLayout();
    HRESULT CreateGraphicsResources();
    void    DiscardGraphicsResources();
    void    OnPaint();
    void    Resize();


    static LRESULT HandleMessage(BaseWindow* concreteWindow, HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
    CircleWindow() : BaseWindow(HandleMessage), pFactory(NULL), pRenderTarget(NULL), pBrush(NULL) {}

    LRESULT CircleHandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	
};

