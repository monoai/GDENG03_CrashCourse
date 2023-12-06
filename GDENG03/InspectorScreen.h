#pragma once
#include "AUIScreen.h"
#include "GameObjectManager.h"
#include "UIManager.h"
#include "AGameObject.h"
#include "Texture.h"

class AGameObject;
class Texture;

class InspectorScreen : public AUIScreen
{
public:
	InspectorScreen(std::string name);
	void SendResult(std::string materialPath);
private:
	std::vector<std::string> split(const std::string& s, char delim);
	virtual void drawUI() override;
	void transUpdate();
	void FormatMatImage();

	AGameObject* selectedObj = nullptr;
	const std::string DEFAULT_MATERIAL = "None";
	std::string materialPath = DEFAULT_MATERIAL;
	std::string materialName = DEFAULT_MATERIAL;
	Texture* materialDisplay;

	float pos[3] = { 0.0f, 0.0f, 0.0f };
	float rot[3] = { 0.0f, 0.0f, 0.0f };
	float scale[3] = { 1.0f, 1.0f, 1.0f };
	bool popupOpen = false;

	int BUTTON_WIDTH = 225;
	int BUTTON_HEIGHT = 20;
};