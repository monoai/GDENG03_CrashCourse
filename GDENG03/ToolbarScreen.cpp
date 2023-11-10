#include "ToolbarScreen.h"
#include "imgui.h"

ToolbarScreen::ToolbarScreen(std::string name) : AUIScreen(name)
{
}

void ToolbarScreen::drawUI()
{
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("New", "Ctrl+N")) {
			}
			if (ImGui::MenuItem("Save", "Ctrl+S")) {
			}
			if (ImGui::MenuItem("Open", "Ctrl+O")) {
			}
			if (ImGui::MenuItem("Exit", "Ctrl+W")) {
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Game Object")) {
			void* shader_byte_code = nullptr;
			size_t size_shader = 0;
			GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
			VertexShader* m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

			if (ImGui::MenuItem("Create Cube")) {
				GameObjectManager::getInstance()->createObject(GameObjectManager::PrimitiveType::CUBE, shader_byte_code, size_shader);
				std::cout << "created cube" << std::endl;
			}
			if (ImGui::MenuItem("Create Sphere")) {
				// placeholder place for future obj
				std::cout << "created sphere" << std::endl;
			}
			if (ImGui::MenuItem("Create Plane")) {
				GameObjectManager::getInstance()->createObject(GameObjectManager::PrimitiveType::PLANE, shader_byte_code, size_shader);
				std::cout << "created plane" << std::endl;
			}
			if (ImGui::BeginMenu("Light")) {
				if (ImGui::MenuItem("Point Light")) {
					// placeholder place for future obj
					std::cout << "created point light" << std::endl;
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}