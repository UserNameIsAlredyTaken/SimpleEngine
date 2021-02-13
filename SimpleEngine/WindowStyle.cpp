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

    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = WindowProc;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = GetModuleHandle(NULL);
    windowClass.hIcon = LoadIcon(0, IDI_APPLICATION);
    windowClass.hCursor = LoadCursor(0, IDC_ARROW);
    windowClass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
    windowClass.lpszMenuName = 0;
    windowClass.lpszClassName = L"CommonWindowClass";

    if (!RegisterClass(&windowClass))
    {
        MessageBox(0, L"RegisterClass Failed.", 0, 0);
        return;
    }
}

PCWSTR WindowStyle::GetName()
{
    return windowClass.lpszClassName;
}
