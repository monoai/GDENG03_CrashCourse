#include "ActionScreen.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "ActionHistory.h"
#include "GameObjectManager.h"

ActionScreen::ActionScreen(std::string name) : AUIScreen(name)
{

}

void ActionScreen::drawUI()
{
	ImGui::Begin("Actions", 0, ImGuiWindowFlags_NoResize);
	ImGui::SetWindowSize(ImVec2(200, 100));
	ImGui::SameLine();

	ImGui::BeginDisabled(!ActionHistory::getInstance()->hasRemainingUndoActions());
	if (ImGui::Button("Undo")) {
		if (ActionHistory::getInstance()->hasRemainingUndoActions()) {
			GameObjectManager::getInstance()->applyEditorAction(ActionHistory::getInstance()->undoAction());
		}
	}
	ImGui::EndDisabled();
	ImGui::SameLine();

	ImGui::BeginDisabled(!ActionHistory::getInstance()->hasRemainingRedoActions());
	if (ImGui::Button("Redo")) {
		if (ActionHistory::getInstance()->hasRemainingRedoActions()) {
			GameObjectManager::getInstance()->applyEditorAction(ActionHistory::getInstance()->redoAction());
		}
	}
	ImGui::EndDisabled();

	ImGui::End();
}