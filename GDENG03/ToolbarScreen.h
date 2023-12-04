#pragma once
#include "AUIScreen.h"
#include <iostream>
#include "GameObjectManager.h"
#include "GraphicsEngine.h"
#include "VertexShader.h"
#include "imfilebrowser.h"

class ToolbarScreen : public AUIScreen
{
public:
	ToolbarScreen(std::string name);
private:
	virtual void drawUI() override;

	bool openSceneSelected = false;

	ImGui::FileBrowser* saveSceneDialog;
	ImGui::FileBrowser* openSceneDialog;
};