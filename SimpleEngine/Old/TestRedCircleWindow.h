#pragma once
#include "../BaseWindow.h"
#include <d2d1.h>
#pragma comment(lib, "d2d1")

class TestRedCircleWindow : public BaseWindow
{
    ID2D1Factory* pFactory;
    ID2D1HwndRenderTarget* pRenderTarget;
    ID2D1SolidColorBrush* pBrush;
    D2D1_ELLIPSE ellipse;

    void    CalculateLayout();
    HRESULT CreateGraphicsResources();
    void    DiscardGraphicsResources();
    void    OnPaint();
    void    Resize();


    static LRESULT HandleMessage(BaseWindow* concreteWindow, HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
    TestRedCircleWindow() : BaseWindow(HandleMessage), pFactory(NULL), pRenderTarget(NULL), pBrush(NULL) {}

    LRESULT RedCircleHandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

