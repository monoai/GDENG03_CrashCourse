#include "ProfilerScreen.h"
#include "imgui.h"

ProfilerScreen::ProfilerScreen(std::string name) : AUIScreen(name)
{
}

void ProfilerScreen::drawUI()
{
	ImGui::Begin("GDENG03 Engine Profiler");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}
