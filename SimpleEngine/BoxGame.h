#pragma once
#include "Game.h"

class BoxGame : public Game
{
public:
	BoxGame(HINSTANCE hInstance);
	~BoxGame();

	bool Initialize();


private:

	NECESSARY_STATIC_FUNCTIONS(BoxGame);

	LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void Update(const GameTimer& gt);
	void Draw(const GameTimer& gt);
};

