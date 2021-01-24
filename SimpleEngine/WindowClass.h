#pragma once
#include <windows.h>

/// <summary>
/// Global window class for all windows of the app
/// </summary>
class WindowClass
{
	//Singletone (probably thread safe)
public:
	static WindowClass& getInstance() {
		static WindowClass instance;
		return instance;
	}

	PCWSTR GetName();

private:
	WindowClass();
	~WindowClass() = default;
	WindowClass(const WindowClass&) = delete;
	WindowClass& operator=(const WindowClass&) = delete;

	WNDCLASS windowClass;


};

