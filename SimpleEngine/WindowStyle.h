#pragma once
#include <windows.h>

/// <summary>
/// Global window class for all windows of the app
/// </summary>
class WindowStyle
{
	//Singletone (probably thread safe)
public:
	static WindowStyle& getInstance() {
		static WindowStyle instance;
		return instance;
	}

	PCWSTR GetName();

private:
	WindowStyle();
	~WindowStyle() = default;
	WindowStyle(const WindowStyle&) = delete;
	WindowStyle& operator=(const WindowStyle&) = delete;

	WNDCLASS windowClass;


};

