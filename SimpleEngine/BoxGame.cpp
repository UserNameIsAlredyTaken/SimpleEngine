#include "BoxGame.h"


BoxGame::BoxGame(HINSTANCE hInstance)
	: Game(hInstance)
{
	mMainWndCaption = L"RedrawGame";
}

BoxGame::~BoxGame()
{
}

bool BoxGame::Initialize()
{
	NECESSARY_STATIC_INIT();

	return true;
}
