#pragma once

#include <functional>

#include "../Game.h"
#include <DirectXColors.h>

using namespace DirectX;



class RedrawGame : public Game
{
public:
	RedrawGame(HINSTANCE hInstance);
	~RedrawGame();

	bool Initialize();

	
	NECESSARY_STATIC_FUNCTIONS(RedrawGame);

private:	
	
	XMVECTORF32 currentColor;

	XMVECTORF32 selectedColor = Colors::LightSteelBlue;
	XMVECTORF32 unselectedColor = Colors::Bisque;

	LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void Update(const GameTimer& gt);
	void Draw(const GameTimer& gt);
	void OnResize();

};