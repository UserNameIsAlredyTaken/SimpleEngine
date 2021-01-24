#include "Game.h"
#include "CircleWindow.h"
#include "WindowClass.h"


int Game::Run()
{
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

