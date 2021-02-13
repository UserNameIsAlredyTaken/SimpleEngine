#pragma once

#include "BaseWindow.h"
#include <d2d1.h>
#include <wrl.h>
#pragma comment(lib, "d2d1")

using namespace Microsoft::WRL;

class MainWindow : public BaseWindow
{
	void Resize();

	static LRESULT HandleMessage(BaseWindow* concreteWindow, HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	MainWindow() : BaseWindow(HandleMessage){}

	LRESULT MainHandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

