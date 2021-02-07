#pragma once

#include<memory>
#include "BaseWindow.h"
#include "set"

class Game
{
private:
	std::set<std::shared_ptr<BaseWindow>> windows;

	void CreateWindows();
	void ShowWindows();

public:
	int Run();


};

