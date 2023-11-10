#pragma once
#include <string>
#include "UIManager.h"

class UIManager;

class AUIScreen
{
protected:
	AUIScreen(std::string name);
	~AUIScreen();

	std::string getName();
	virtual void drawUI() = 0;

	std::string name;

	friend class UIManager;
};