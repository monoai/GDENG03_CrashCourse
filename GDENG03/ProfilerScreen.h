#pragma once
#include "AUIScreen.h"

class UIManager;
class ProfilerScreen : public AUIScreen
{
public:
	ProfilerScreen(std::string name);
private:
	virtual void drawUI() override;
};