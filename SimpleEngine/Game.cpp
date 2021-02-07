#include "Game.h"
#include "CircleWindow.h"
#include "TestRedCircleWindow.h"
#include "WindowStyle.h"
#include <memory>


void Game::CreateWindows()
{
    std::shared_ptr<BaseWindow> newWindow = std::make_shared<TestRedCircleWindow>();

    if (newWindow->Create(L"Red Circle", WS_OVERLAPPEDWINDOW))
    {
        windows.insert(newWindow);
    }

    newWindow = std::make_shared<CircleWindow>();

    if (newWindow->Create(L"Red Circle", WS_OVERLAPPEDWINDOW))
    {
        windows.insert(newWindow);
    }
}

void Game::ShowWindows()
{
    for (auto&& window : windows) 
    {
        ShowWindow(window->GetHwnd(), SW_SHOWDEFAULT);
    }
}

int Game::Run()
{    
    CreateWindows();
    ShowWindows();


    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

