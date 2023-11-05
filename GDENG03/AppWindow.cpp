#include "AppWindow.h"
#include "EngineTime.h"
#include "InputSystem.h"
#include "SceneCameraHandler.h"
#include <array>
#include <random>
#include <algorithm>
#include <limits>

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
	
	InputSystem::initialize();
	//InputSystem::getInstance()->addListener(this);

	EngineTime::initialize();
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();
	
	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	// imgui init
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(this->m_hwnd);
	ImGui_ImplDX11_Init(GraphicsEngine::get()->getd3dDevice(), GraphicsEngine::get()->getImmediateDeviceContext()->getDeviceContext());

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	std::uniform_real_distribution<> posVal(-1.50, 1.50);
	std::uniform_real_distribution<> speedVal(-5.0, 5.00);

	for (int i = 0; i < 50; i++) {
		Cube* cubeObject = new Cube("Cube", shader_byte_code, size_shader);

		cubeObject->setAnimSpeed(speedVal(rng));
		cubeObject->setPosition(Vector3D(posVal(rng), posVal(rng), 0.0f));
		//cubeObject->setAnimSpeed(3.0f);
		//cubeObject->setPosition(Vector3D(0.0f, 0.0f, 0.0f));
		cubeObject->setScale(Vector3D(0.5, 0.5, 0.5));
		this->cubeList.push_back(cubeObject);
		//std::cout << "Created" << std::endl;
	}

	// only release if you're done compiling shaders
	GraphicsEngine::get()->releaseCompiledShader();

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);

	// remember that if we need to do pixel shading stuff, do it here

	GraphicsEngine::get()->releaseCompiledShader();

	SceneCameraHandler::initialize();
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	InputSystem::getInstance()->update();
	// remember to set the shaders first else null errors
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, color);

	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	// (Your code process and dispatch Win32 messages)

	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	if(demoCheck == true) {
		ImGui::ShowDemoWindow(); // Show demo window! :)
	}
	// TODO: add a better way to make windows here
	///*
		ImGuiWindowFlags window_flags = 0;
		window_flags |= ImGuiWindowFlags_NoResize;
		const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 100, main_viewport->WorkPos.y + 20), ImGuiCond_None);
		ImGui::SetNextWindowSize(ImVec2(350, 300), ImGuiCond_None);

		if (!ImGui::Begin("Scene Settings", NULL, window_flags))
		{
			// Early out if the window is collapsed, as an optimization.
			ImGui::End();
			return;
		}

		ImGui::PushItemWidth(ImGui::GetFontSize() * -12);
		ImGui::Text("Below are settings for configuring the Scene");
		
		ImGui::Checkbox("Show Demo Window", &demoCheck);
		ImGui::ColorEdit3("clear color", (float*)&color);
		if (ImGui::Button(playAnim ? "Pause Animation" : "Resume Animation")) {
			playAnim = !playAnim;
			std::cout << "play anim is now: " << playAnim << std::endl;
		}

		ImGui::End();
	//*/

	for (unsigned int i = 0; i < this->cubeList.size(); i++) {
		if (playAnim) {
			this->cubeList[i]->update(EngineTime::getDeltaTime());
		}
		this->cubeList[i]->draw(rc.right - rc.left, rc.bottom - rc.top, this->m_vs, this->m_ps);
		
		//std::cout << "updating cubes" << std::endl;
	}

	SceneCameraHandler::getInstance()->update();

	// Rendering
	// (Your code clears your framebuffer, renders your other stuff etc.)
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	// (Your code calls swapchain's Present() function)

	m_swap_chain->present(true);

	/*
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	//SET THE INDICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
	*/
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	InputSystem::getInstance()->removeListener(this);
	InputSystem::getInstance()->destroy();
	m_vb->release();
	m_ib->release();
	m_cb->release();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	SceneCameraHandler::destroy();
	GraphicsEngine::get()->release();
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

void AppWindow::onKeyDown(int key)
{
	if (key == 'W') {
		std::cout << "Key W pressed down" << std::endl;
	}
}

void AppWindow::onKeyUp(int key)
{
	if (key == 'W') {
		std::cout << "Key W pressed up" << std::endl;
	}
}

void AppWindow::onMouseMove(const Point mouse_pos)
{

}

void AppWindow::onLeftMouseDown(const Point mouse_pos)
{
	std::cout << "Left mouse down" << std::endl;
}

void AppWindow::onLeftMouseUp(const Point mouse_pos)
{
	std::cout << "Left mouse up" << std::endl;
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
