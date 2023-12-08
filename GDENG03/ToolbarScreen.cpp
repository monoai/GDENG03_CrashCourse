#include "ToolbarScreen.h"
#include "imgui.h"
#include "imfilebrowser.h"
#include "AppWindow.h"
#include "SceneWriter.h"
#include "SceneReader.h"

ToolbarScreen::ToolbarScreen(std::string name) : AUIScreen(name)
{
	this->openSceneDialog = new ImGui::FileBrowser();
	this->openSceneDialog->SetTitle("Open Scene");
	this->openSceneDialog->SetTypeFilters({ ".iet" });

	this->saveSceneDialog = new ImGui::FileBrowser(ImGuiFileBrowserFlags_EnterNewFilename);
	this->saveSceneDialog->SetTitle("Save Scene");
	this->saveSceneDialog->SetTypeFilters({ ".iet" });
}

void ToolbarScreen::drawUI()
{
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("New", "Ctrl+N")) {
			}
			if (ImGui::MenuItem("Save", "Ctrl+S")) {
				this->saveSceneDialog->Open();
			}
			if (ImGui::MenuItem("Open", "Ctrl+O")) {
				this->openSceneDialog->Open();
			}
			if (ImGui::MenuItem("Exit", "Ctrl+W")) {
				exit(0);
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Game Object")) {
			void* shader_byte_code = nullptr;
			size_t size_shader = 0;
			GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
			VertexShader* m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

			if (ImGui::MenuItem("Create Cube")) {
				GameObjectManager::getInstance()->createObject(AGameObject::PrimitiveType::CUBE);
				std::cout << "created cube" << std::endl;
			}
			if (ImGui::MenuItem("Create Textured Cube")) {
				GameObjectManager::getInstance()->createObject(AGameObject::PrimitiveType::TEXTURED_CUBE);
				std::cout << "created cube" << std::endl;
			}
			if (ImGui::MenuItem("Create Sphere")) {
				// placeholder place for future obj
				std::cout << "created sphere" << std::endl;
			}
			if (ImGui::MenuItem("Create Plane")) {
				GameObjectManager::getInstance()->createObject(AGameObject::PrimitiveType::PLANE);
				std::cout << "created plane" << std::endl;
			}
			if (ImGui::BeginMenu("Light")) {
				if (ImGui::MenuItem("Point Light")) {
					// placeholder place for future obj
					std::cout << "created point light" << std::endl;
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Physics")) {
				if (ImGui::MenuItem("Create Physics Cube")) {
					GameObjectManager::getInstance()->createObject(AGameObject::PrimitiveType::PHYSICS_CUBE);
					std::cout << "created phys cube" << std::endl;
				}
				if (ImGui::MenuItem("Create Multiple Physics Cube")) {
					for (int i = 0; i < 30; i++) {
						GameObjectManager::getInstance()->createObject(AGameObject::PrimitiveType::PHYSICS_CUBE);
					}
					std::cout << "created multiple phys cube" << std::endl;
				}
				if (ImGui::MenuItem("Create Physics Plane")) {
					GameObjectManager::getInstance()->createObject(AGameObject::PrimitiveType::PHYSICS_PLANE);
					std::cout << "created phys cube" << std::endl;
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	this->openSceneDialog->Display();
	this->saveSceneDialog->Display();

	if (this->saveSceneDialog->HasSelected())
	{
		SceneWriter writer = SceneWriter(this->saveSceneDialog->GetSelected().string());
		writer.writeToFile();

		this->saveSceneDialog->ClearSelected();
		this->saveSceneDialog->Close();
	}

	else if (this->openSceneDialog->HasSelected()) {
		GameObjectManager::getInstance()->deleteAll();
		GameObjectManager::getInstance()->setSelectedObject(NULL);
		SceneReader reader = SceneReader(this->openSceneDialog->GetSelected().string());
		reader.readFromFile();

		this->openSceneDialog->ClearSelected();
		this->openSceneDialog->Close();
	}
}