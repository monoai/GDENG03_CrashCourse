#include "UIManager.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"

UIManager* UIManager::sharedInstance = NULL;

UIManager* UIManager::getInstance()
{
	return sharedInstance;
}

void UIManager::initialize(HWND m_hwnd)
{
	sharedInstance = new UIManager(m_hwnd);
}

void UIManager::destroy()
{
	delete sharedInstance;
}

void UIManager::drawAllUI()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	for (unsigned int i = 0; i < this->uiList.size(); i++) {
		this->uiList[i]->drawUI();
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void UIManager::setEnabled(std::string uiName, bool flag)
{
	if (this->uiTable[uiName] != nullptr)
	{
		this->uiTable[uiName]->SetEnabled(flag);
	}
}

AUIScreen* UIManager::findUIByName(std::string uiName)
{
	if (this->uiTable[uiName] != nullptr)
	{
		return this->uiTable[uiName];
	}
	else
	{
		return nullptr;
	}
}

void UIManager::pushList(std::string name, AUIScreen* screen)
{
	this->uiTable[name] = screen;
	this->uiList.push_back(screen);
}

UIManager::UIManager(HWND m_hwnd)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(m_hwnd);
	ImGui_ImplDX11_Init(GraphicsEngine::get()->getd3dDevice(), GraphicsEngine::get()->getImmediateDeviceContext()->getDeviceContext());
}

UIManager::~UIManager()
{
}
