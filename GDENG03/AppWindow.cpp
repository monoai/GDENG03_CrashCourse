#include "AppWindow.h"
#include "EngineTime.h"
#include "InputSystem.h"
#include "SceneCameraHandler.h"
#include "UIManager.h"
#include "GameObjectManager.h"
#include "BaseComponentSystem.h"
#include "ShaderLibrary.h"
#include "TextureManager.h"
#include "EngineBackend.h"
#include "ActionHistory.h"
#include <array>
#include <random>
#include <algorithm>
#include <limits>
#include <reactphysics3d/reactphysics3d.h>

// rng Variables
// try to refactor later
std::random_device dev;
std::mt19937 rng(dev());

AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();

	initializeEngine();
	initializeUI();
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	InputSystem::getInstance()->update();
	// remember to set the shaders first else null errors
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, color);

	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	EngineBackend* backend = EngineBackend::getInstance();
	//std::cout << "mode is: " << backend->getMode() << std::endl;
	if (backend->getMode() == EngineBackend::EditorMode::PLAY) {
		BaseComponentSystem::getInstance()->getPhysicsSystem()->updateAllComponents();
		GameObjectManager::getInstance()->updateAll();
	} else if (backend->getMode() == EngineBackend::EditorMode::EDITOR) {
		GameObjectManager::getInstance()->updateAll();
	} else if (backend->getMode() == EngineBackend::EditorMode::PAUSED) {
		if (backend->insideFrameStep()) {
			BaseComponentSystem::getInstance()->getPhysicsSystem()->updateAllComponents();
			GameObjectManager::getInstance()->updateAll();
			backend->endFrameStep();
		}
	}

	// systems
	GameObjectManager::getInstance()->renderAll(rc.right - rc.left, rc.bottom - rc.top);
	
	SceneCameraHandler::getInstance()->update();

	UIManager::getInstance()->drawAllUI();

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	InputSystem::getInstance()->removeListener(this);
	InputSystem::getInstance()->destroy();
	//m_vb->release();
	//m_ib->release();
	//m_cb->release();
	//m_swap_chain->release();
	//m_vs->release();
	//m_ps->release();
	SceneCameraHandler::destroy();
	GameObjectManager::destroy();
	BaseComponentSystem::destroy();
	UIManager::destroy();
	delete GraphicsEngine::get();
	ShaderLibrary::destroy();
	TextureManager::destroy();
	EngineBackend::destroy();
	ActionHistory::destroy();
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void AppWindow::onFocus()
{
	InputSystem::getInstance()->addListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::getInstance()->removeListener(this);
}

void AppWindow::initializeEngine()
{
	// Try to initialize the GraphicsEngine via the constructor
	GraphicsEngine* m_engine = nullptr;
	try {
		GraphicsEngine::initialize();
	}
	catch (const std::exception& ex) { std::cout << ex.what() << std::endl; }
	EngineBackend::initialize();

	RECT rc = this->getClientWindowRect();
	m_swap_chain = GraphicsEngine::get()->createSwapChain(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	// Initialize systems
	ShaderLibrary::initialize();
	TextureManager::initialize();
	InputSystem::initialize();
	//InputSystem::getInstance()->addListener(this);
	GameObjectManager::initialize();
	BaseComponentSystem::initialize();
	EngineTime::initialize();
	SceneCameraHandler::initialize();
	ActionHistory::initialize();
}

void AppWindow::initializeUI()
{
	UIManager::initialize(m_hwnd);
	UINames names;
	ToolbarScreen* toolscreen = new ToolbarScreen(names.MENU_SCREEN);
	OutlinerScreen* outlinerscreen = new OutlinerScreen(names.HIERARCHY_SCREEN);
	InspectorScreen* inspectorscreen = new InspectorScreen(names.INSPECTOR_SCREEN);
	ProfilerScreen* profilerscreen = new ProfilerScreen(names.PROFILER_SCREEN);
	ScenePlayScreen* sceneplayscreen = new ScenePlayScreen(names.SCENEPLAY_SCREEN);
	ActionScreen* actionscreen = new ActionScreen(names.ACTION_SCREEN);
	UIManager::getInstance()->pushList(toolscreen);
	UIManager::getInstance()->pushList(outlinerscreen);
	UIManager::getInstance()->pushList(inspectorscreen);
	UIManager::getInstance()->pushList(profilerscreen);
	UIManager::getInstance()->pushList(sceneplayscreen);
	UIManager::getInstance()->pushList(actionscreen);
}

void AppWindow::onKeyDown(int key)
{
	if (key == 'W') {
		//std::cout << "Key W pressed down" << std::endl;
	}
}

void AppWindow::onKeyUp(int key)
{
	if (key == 'W') {
		//std::cout << "Key W pressed up" << std::endl;
	}
}

void AppWindow::onMouseMove(const Point mouse_pos)
{

}

void AppWindow::onLeftMouseDown(const Point mouse_pos)
{
	//std::cout << "Left mouse down" << std::endl;
}

void AppWindow::onLeftMouseUp(const Point mouse_pos)
{
	//std::cout << "Left mouse up" << std::endl;
}

void AppWindow::onRightMouseDown(const Point mouse_pos)
{
	std::cout << "Right mouse down" << std::endl;
	//rmouseClick = true;
}

void AppWindow::onRightMouseUp(const Point mouse_pos)
{
	std::cout << "Right mouse up" << std::endl;
	//rmouseClick = false;
}
