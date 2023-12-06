#include "InspectorScreen.h"
#include "imgui.h"
#include "ActionHistory.h"
#include "MaterialScreen.h"
#include "TextureManager.h"
#include "TexturedCube.h"
#include "TextureRenderer.h"

InspectorScreen::InspectorScreen(std::string name) : AUIScreen(name)
{
}

void InspectorScreen::SendResult(std::string materialPath)
{
	TexturedCube* texturedObj = static_cast<TexturedCube*>(this->selectedObj);
	texturedObj->getRenderer()->setMaterialPath(materialPath);
	this->popupOpen = false;
}

std::vector<std::string> InspectorScreen::split(const std::string& s, char delim)
{
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> elems;
	while (std::getline(ss, item, delim)) {
		elems.push_back(std::move(item));
	}
	return elems;
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

		// physics
		ImGui::Text("Rigidbody: None");
		if (ImGui::Button("Add Rigidbody", ImVec2(BUTTON_WIDTH, BUTTON_HEIGHT))) {

		}

		// materials
		if (this->selectedObj->getObjectType() != AGameObject::TEXTURED_CUBE)
		{
			return;
		}

		TexturedCube* texturedObj = static_cast<TexturedCube*>(this->selectedObj);
		this->materialPath = texturedObj->getRenderer()->getMaterialPath();
		this->FormatMatImage();
		ImGui::SetCursorPosX(50);
		ImGui::Image(static_cast<void*>(this->materialDisplay->getShaderResource()), ImVec2(150, 150));

		std::vector<std::string> paths = split(this->materialPath, '\\');
		this->materialName = paths[paths.size() - 1];
		std::string displayText = "Material: " + this->materialName;
		ImGui::Text(displayText.c_str());
		if (ImGui::Button("Add Material", ImVec2(BUTTON_WIDTH, BUTTON_HEIGHT))) {
			this->popupOpen = !this->popupOpen;
			UINames uiNames;
			MaterialScreen* materialScreen = static_cast<MaterialScreen*>(UIManager::getInstance()->findUIByName(uiNames.MATERIAL_SCREEN));
			materialScreen->linkInspectorScreen(this, this->materialPath);
			UIManager::getInstance()->setEnabled(uiNames.MATERIAL_SCREEN, this->popupOpen);
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

void InspectorScreen::FormatMatImage()
{
	//convert to wchar format
	std::string textureString = this->materialPath;
	std::wstring widestr = std::wstring(textureString.begin(), textureString.end());
	const wchar_t* texturePath = widestr.c_str();

	this->materialDisplay = static_cast<Texture*>(TextureManager::getInstance()->createTextureFromFile(texturePath));
}
