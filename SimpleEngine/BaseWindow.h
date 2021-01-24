#pragma once
#include <windows.h>
#include "WindowClass.h"


class BaseWindow
{
public:
    HWND m_hwnd;

    
    LRESULT HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
    { 
        return handlerFunction(this, hwnd, uMsg, wParam, lParam);
    }

    BaseWindow(LRESULT (*handlerFunction)(BaseWindow* concreteWindow, HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)) : m_hwnd(NULL), handlerFunction(handlerFunction){ }

    BOOL Create(
        PCWSTR lpWindowName,
        DWORD dwStyle,
        DWORD dwExStyle = 0,
        int x = CW_USEDEFAULT,
        int y = CW_USEDEFAULT,
        int nWidth = CW_USEDEFAULT,
        int nHeight = CW_USEDEFAULT,
        HWND hWndParent = 0,
        HMENU hMenu = 0
    )
    {
        m_hwnd = CreateWindowEx(
            dwExStyle, WindowClass::getInstance().GetName(), lpWindowName, dwStyle, x, y,
            nWidth, nHeight, hWndParent, hMenu, GetModuleHandle(NULL), this
        );

        return (m_hwnd ? TRUE : FALSE);
    }

    HWND GetHwnd() const { return m_hwnd; }
 

private:
    LRESULT (*handlerFunction)(BaseWindow* concreteWindow, HWND, UINT, WPARAM, LPARAM); //ponter to a function that handles messages for a window
};