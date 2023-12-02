#pragma once
#include "AUIScreen.h"
class ScenePlayScreen : public AUIScreen
{
public:
	ScenePlayScreen(std::string name);
private:

	virtual void drawUI() override;
	friend class UIManager;

	bool played = false;
	bool paused = false;
};