#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include <vector>

struct vec3 {
	float x, y, z;
};

struct vertex {
	vec3 position;
};

class Quad {
public:
	Quad(vertex list[], UINT size_list);
	VertexBuffer* getVB();
private:
	VertexBuffer* m_vb;
};

class AppWindow: public Window
{
public:
	AppWindow();
	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
private:
	SwapChain* m_swap_chain;
	std::vector<Quad> quads;
};

