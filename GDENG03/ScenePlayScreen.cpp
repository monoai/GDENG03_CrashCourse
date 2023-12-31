#include "ScenePlayScreen.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "EngineBackend.h"


ScenePlayScreen::ScenePlayScreen(std::string name) : AUIScreen(name)
{

}

void ScenePlayScreen::drawUI()
{
	EngineBackend* backend = EngineBackend::getInstance();

	ImGui::Begin("Scene Play Options", 0, ImGuiWindowFlags_NoResize);
	ImGui::SetWindowSize(ImVec2(200, 100));
	ImGui::SameLine();

	if (backend->getMode() == EngineBackend::EDITOR) {
		if (ImGui::Button("Play")) { EngineBackend::getInstance()->setMode(EngineBackend::PLAY); }
	}

	else if (backend->getMode() != EngineBackend::EDITOR) {
		if (ImGui::Button("Stop")) { EngineBackend::getInstance()->setMode(EngineBackend::EDITOR); }
	}

	ImGui::SameLine();

	if (backend->getMode() == EngineBackend::PLAY) {
		if (ImGui::Button("Pause")) { EngineBackend::getInstance()->setMode(EngineBackend::PAUSED); }
	}
	else if (backend->getMode() == EngineBackend::PAUSED) {
		if (ImGui::Button("Resume")) { EngineBackend::getInstance()->setMode(EngineBackend::PLAY); }
	}

	ImGui::SameLine();

	if (backend->getMode() == EngineBackend::PAUSED && ImGui::Button("Frame Step")) {
		EngineBackend::getInstance()->startFrameStep(); 
	}

	ImGui::End();
}