#include "MainWindow.h"


LRESULT MainWindow::HandleMessage(BaseWindow* concreteWindow, HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return ((MainWindow*)concreteWindow)->MainHandleMessage(hwnd, uMsg, wParam, lParam);
}


LRESULT MainWindow::MainHandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {        

    case WM_SIZE:
        Resize();
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}