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

	/*
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

	*/

	vertex list[] = {
		{-0.5f,-0.5f,0.0f, -0.32f,-0.11f,0.0f,  0,0,0,  0,1,0 },
		{-0.5f,0.5f,0.0f,  -0.11f,0.78f,0.0f,   1,1,0,  0,1,1 },
		{ 0.5f,-0.5f,0.0f, 0.75f,-0.73f,0.0f,   0,0,1,  1,0,0 },
		{ 0.5f,0.5f,0.0f,  0.88f,0.77f,0.0f,    1,1,1,  0,0,1 }
	};

	UINT size_list = ARRAYSIZE(list);
	
	///*
	m_vb = GraphicsEngine::get()->createVertexBuffer();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();


	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	constant cc;
	cc.m_angle = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
	//*/
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	unsigned long new_time = 0;
	if (m_old_time)
		new_time = ::GetTickCount64() - m_old_time;
	m_delta_time = new_time / 1000.0f;
	m_old_time = ::GetTickCount64();

	m_angle += 1.57f * m_delta_time;
	constant cc;
	cc.m_angle = m_angle;

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
	m_swap_chain->present(true);
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
	m_vb->release();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	GraphicsEngine::get()->release();
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
