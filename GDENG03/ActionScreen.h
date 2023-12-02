#pragma once
#include "AUIScreen.h"

class ActionScreen : public AUIScreen
{
public:
	ActionScreen(std::string name);
private:

	virtual void drawUI() override;
	friend class UIManager;

};