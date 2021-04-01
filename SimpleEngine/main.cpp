#ifndef UNICODE
#define UNICODE
#endif 
#define _USE_MATH_DEFINES

#include <iostream>
#include "Game.h"
#include "RedrawGame.h"
#include <windows.h>
#include <math.h>
#include "BoxGame.h"




int main()
{
    // RedrawGame game(GetModuleHandle(NULL));
    try
    {
        BoxGame game(GetModuleHandle(NULL));
        if (!game.Initialize())
            return 0;
        
        return game.Run();
    }
    catch(DxException& e)
    {
        MessageBox(nullptr, e.ToString().c_str(), L"HR Failed", MB_OK);
        return 0;
    }
}

