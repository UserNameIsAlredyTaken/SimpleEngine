#include "Game.h"
#include "CircleWindow.h"
#include "TestRedCircleWindow.h"
#include "WindowStyle.h"


void CreateWindows()
{
    TestRedCircleWindow redCircle;
    if (!redCircle.Create(L"Red Circle", WS_OVERLAPPEDWINDOW))
        return;
    ShowWindow(redCircle.GetHwnd(), SW_SHOWDEFAULT);


    CircleWindow circle;
    if (!circle.Create(L"Circle", WS_OVERLAPPEDWINDOW))
        return;
    ShowWindow(circle.GetHwnd(), SW_SHOWDEFAULT);
}

int Game::Run()
{    
    //CreateWindows();

    TestRedCircleWindow redCircle;
    if (!redCircle.Create(L"Red Circle", WS_OVERLAPPEDWINDOW))
        return 0;
    ShowWindow(redCircle.GetHwnd(), SW_SHOWDEFAULT);

    CircleWindow circle;
    if (!circle.Create(L"Circle", WS_OVERLAPPEDWINDOW))
        return 0;
    ShowWindow(circle.GetHwnd(), SW_SHOWDEFAULT);




    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

