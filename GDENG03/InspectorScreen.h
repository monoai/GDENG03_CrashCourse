#pragma once
#include "AUIScreen.h"
#include "GameObjectManager.h"
#include "UIManager.h"
#include "AGameObject.h"

class AGameObject;

class InspectorScreen : public AUIScreen
{
public:
	InspectorScreen(std::string name);
private:
	virtual void drawUI() override;
	void transUpdate();

	AGameObject* selectedObj = nullptr;

	float pos[3] = { 0.0f, 0.0f, 0.0f };
	float rot[3] = { 0.0f, 0.0f, 0.0f };
	float scale[3] = { 1.0f, 1.0f, 1.0f };
};