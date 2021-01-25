#pragma once

#include "WindowStyle.h"
#include "BaseWindow.h"


static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    BaseWindow* pWindow = NULL;

    if (uMsg == WM_NCCREATE)
    {
        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
        pWindow = (BaseWindow*)pCreate->lpCreateParams;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pWindow);

        pWindow->m_hwnd = hwnd;
    }
    else
    {
        pWindow = (BaseWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }
    if (pWindow)
    {
        return pWindow->HandleMessage(hwnd, uMsg, wParam, lParam);
    }
    else
    {
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}


WindowStyle::WindowStyle()
{
    windowClass = { 0 };

    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = GetModuleHandle(NULL);
    windowClass.lpszClassName = L"CommonWindowClass";

    RegisterClass(&windowClass);
}

PCWSTR WindowStyle::GetName()
{
    return windowClass.lpszClassName;
}
