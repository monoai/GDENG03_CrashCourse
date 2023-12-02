#include "InspectorScreen.h"
#include "imgui.h"
#include "ActionHistory.h"

InspectorScreen::InspectorScreen(std::string name) : AUIScreen(name)
{
}

void InspectorScreen::drawUI()
{
	ImGui::Begin("Inspector Window");
	//AGameObject* selectedObject = nullptr;
	ImGui::SetWindowPos(ImVec2(UIManager::WINDOW_WIDTH - 275, 20));
	ImGui::SetWindowSize(ImVec2(250, UIManager::WINDOW_HEIGHT));
	this->selectedObj = GameObjectManager::getInstance()->getSelectedObject();

	if (this->selectedObj != NULL) {
		ImGui::Text("Selected Object: %s", this->selectedObj->getName().c_str());

		// get the values first
		this->pos[0] = this->selectedObj->getLocalPosition().getX();
		this->pos[1] = this->selectedObj->getLocalPosition().getY();
		this->pos[2] = this->selectedObj->getLocalPosition().getZ();

		this->rot[0] = this->selectedObj->getLocalRotation().getX();
		this->rot[1] = this->selectedObj->getLocalRotation().getY();
		this->rot[2] = this->selectedObj->getLocalRotation().getZ();

		this->scale[0] = this->selectedObj->getLocalScale().getX();
		this->scale[1] = this->selectedObj->getLocalScale().getY();
		this->scale[2] = this->selectedObj->getLocalScale().getZ();
		bool enabled = this->selectedObj->isEnabled();

		if (ImGui::Checkbox("Enabled", &enabled)) { 
			this->selectedObj->setEnabled(enabled); 
		}
		if (ImGui::DragFloat3("Position", this->pos)) {
			this->transUpdate(); 
		}
		if (ImGui::DragFloat3("Rotation", this->rot)) {
			this->transUpdate(); 
		}
		if (ImGui::DragFloat3("Scale", this->scale)) {
			this->transUpdate(); 
		}

	}
	else {
		ImGui::Text("No selected object.");
	}
	ImGui::End();
}

void InspectorScreen::transUpdate()
{
	if (this->selectedObj != NULL) {
		ActionHistory::getInstance()->startRecordAction(this->selectedObj);
		this->selectedObj->setPosition(Vector3D(this->pos[0], this->pos[1], this->pos[2]));
		this->selectedObj->setRotation(Vector3D(this->rot[0], this->rot[1], this->rot[2]));
		this->selectedObj->setScale(Vector3D(this->scale[0], this->scale[1], this->scale[2]));
		ActionHistory::getInstance()->endRecordAction();
	}
}