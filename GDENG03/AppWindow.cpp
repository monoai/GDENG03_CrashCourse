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

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	std::uniform_real_distribution<> posVal(-2.00, 2.00);
	std::uniform_real_distribution<> speedVal(-5.0, 5.00);

	for (int i = 0; i < 10; i++) {
		Cube* cubeObject = new Cube("Cube", shader_byte_code, size_shader);

		cubeObject->setAnimSpeed(speedVal(rng));
		cubeObject->setPosition(Vector3D(posVal(rng), posVal(rng), 0.0f));
		cubeObject->setScale(Vector3D(1.0, 1.0, 1.0));
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
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0.3f, 0.4f, 1);

	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	for (int i = 0; i < this->cubeList.size(); i++) {
		this->cubeList[i]->update(EngineTime::getDeltaTime());
		this->cubeList[i]->draw(rc.right - rc.left, rc.bottom - rc.top, this->m_vs, this->m_ps);
		
		//std::cout << "updating cubes" << std::endl;
	}

	SceneCameraHandler::getInstance()->update();

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

	/*
	for (UINT i = 0; i < quads.size(); i++) {
		GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
		GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(quads[i].getVB());

		GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(quads[i].getVB()->getSizeVertexList(), 0);
	}
	m_swap_chain->present(true);
	*/
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	/*
	for (UINT i = 0; i < quads.size(); i++) {
		quads[i].getVB()->release();
	}
	*/
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

/*
Quad::Quad(vertex list[], UINT size_list)
{
	m_vb = GraphicsEngine::get()->createVertexBuffer();

	GraphicsEngine::get()->createShaders();

	void* shader_byte_code = nullptr;
	UINT size_shader = 0;

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();
}

VertexBuffer* Quad::getVB()
{
	return this->m_vb;
}
*/
