#ifndef UNICODE
#define UNICODE
#endif 

#include <iostream>
#include "Game.h"
#include "RedrawGame.h"
#include <windows.h>

#define _USE_MATH_DEFINES
#include <math.h>



int main()
{
    RedrawGame game(GetModuleHandle(NULL));
    if (!game.Initialize())
        return 0;
    
    return game.Run();
}

