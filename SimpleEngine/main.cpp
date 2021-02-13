#ifndef UNICODE
#define UNICODE
#endif 

#include <iostream>
#include "Game.h"
#include "RedrawGame.h"
#include <windows.h>



int main()
{
    /*Game game;
    game.Run();*/
        

    try
    {
        RedrawGame game(GetModuleHandle(NULL));

        if (!game.Initialize())
            return 0;

        return game.Run();
    }
    catch (DxException& e)
    {
        MessageBox(nullptr, e.ToString().c_str(), L"HR Failed", MB_OK);
        return 0;
    }

    return 0;
}

