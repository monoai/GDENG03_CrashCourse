#pragma once
#include <string>
#include "UIManager.h"

class UIManager;

class AUIScreen
{
public:
	void SetEnabled(bool flag);
protected:
	AUIScreen(std::string name);
	~AUIScreen();

	std::string getName();
	virtual void drawUI() = 0;

	std::string name;
	bool enabled = true;

	friend class UIManager;
};