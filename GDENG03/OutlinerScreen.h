#pragma once
#include "AUIScreen.h"
#include "UIManager.h"
#include "GameObjectManager.h"
#include "AGameObject.h"

class OutlinerScreen : public AUIScreen
{
public:
	OutlinerScreen(std::string);
private:
	std::vector<AGameObject*> objList;
	virtual void drawUI() override;
};