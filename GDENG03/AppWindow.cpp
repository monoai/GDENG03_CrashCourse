#include "AppWindow.h"
#include <array>

AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();
	
	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	vertex q1[] = {
		{-0.95f,-0.5f,0.0f},
		{-0.95f,0.5f,0.0f},
		{-0.5f,-0.5f,0.0f },
		{-0.5f,0.5f,0.0f}
	};

	UINT size_list1 = ARRAYSIZE(q1);

	vertex q2[] = {
		{-0.4f,-0.5f,0.0f},
		{-0.4f,0.5f,0.0f},
		{-0.1f,-0.5f,0.0f },
		{-0.1f,0.5f,0.0f}
	};

	UINT size_list2 = ARRAYSIZE(q2);

	vertex q3[] = {
		{ 0.0f,-0.5f,0.0f},
		{ 0.0f,0.5f,0.0f},
		{ 0.4f,-0.5f,0.0f },
		{ 0.4f,0.5f,0.0f}
	};

	UINT size_list3 = ARRAYSIZE(q3);

	Quad test(q1, size_list1);
	Quad test2(q2, size_list2);
	Quad test3(q3, size_list3);

	quads.push_back(test);
	quads.push_back(test2);
	quads.push_back(test3);
	
	/*
	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(list);

	GraphicsEngine::get()->createShaders();

	void* shader_byte_code = nullptr;
	UINT size_shader = 0;
	GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);

	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);
	*/
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 1, 0, 0, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->setShaders();
	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	for (UINT i = 0; i < quads.size(); i++) {
		GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(quads[i].getVB());

		// FINALLY DRAW THE TRIANGLE
		GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(quads[i].getVB()->getSizeVertexList(), 0);
	}
	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	for (UINT i = 0; i < quads.size(); i++) {
		quads[i].getVB()->release();
	}
	m_swap_chain->release();
	GraphicsEngine::get()->release();
}

Quad::Quad(vertex list[], UINT size_list)
{
	m_vb = GraphicsEngine::get()->createVertexBuffer();

	GraphicsEngine::get()->createShaders();

	void* shader_byte_code = nullptr;
	UINT size_shader = 0;
	GraphicsEngine::get()->getShaderBufferAndSize(&shader_byte_code, &size_shader);

	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);
}

VertexBuffer* Quad::getVB()
{
	return this->m_vb;
}
