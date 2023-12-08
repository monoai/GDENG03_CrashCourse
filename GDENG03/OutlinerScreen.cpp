#include "OutlinerScreen.h"
#include "imgui.h"

OutlinerScreen::OutlinerScreen(std::string name) : AUIScreen(name)
{
}

void OutlinerScreen::drawUI()
{
	ImGui::Begin("Scene Outliner");
	ImGui::SetWindowPos(ImVec2(UIManager::WINDOW_WIDTH - 525, 20));
	ImGui::SetWindowSize(ImVec2(250, UIManager::WINDOW_HEIGHT-100));

	this->objList = GameObjectManager::getInstance()->getAllObjects();

	for (unsigned int i = 0; i < objList.size(); i++) {
		if (ImGui::Button(this->objList[i]->getName().c_str(), ImVec2(235, 0))) {
			GameObjectManager::getInstance()->setSelectedObject(objList[i]->getName());
		}
	}

	ImGui::End();
}
