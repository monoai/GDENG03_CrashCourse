#pragma once
#include "AUIScreen.h"
#include "imfilebrowser.h"
#include "Texture.h"

class InspectorScreen;
class MaterialScreen : public AUIScreen
{

public:
	MaterialScreen(std::string name);
	~MaterialScreen();
	void linkInspectorScreen(InspectorScreen* inspectorScreen, std::string materialPath);

private:
	virtual void drawUI() override;
	friend class UIManager;

	ImGui::FileBrowser* openSceneDialog;
	InspectorScreen* inspectorScreen;

	std::string materialPath;
	Texture* displayTex;

};