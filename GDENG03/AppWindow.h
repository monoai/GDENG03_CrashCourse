#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include <vector>

/*
struct vec3 {
	float x, y, z;
};
*/

struct vertex {
	Vector3D position;
	Vector3D position1;
	Vector3D color;
	Vector3D color1;
};

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	unsigned int m_time;
};

/*
class Quad {
public:
	Quad(vertex list[], UINT size_list);
	VertexBuffer* getVB();
private:
	VertexBuffer* m_vb;
	VertexShader* m_vs;
};
*/

class AppWindow: public Window
{
public:
	AppWindow();

	void updateQuadPosition();

	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
private:
	SwapChain* m_swap_chain;
	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;

	//unsigned long m_old_time = 0;
	//float m_delta_time = 0;
	bool reverse = false;
	float speedFactor = 1.0f;
	float m_angle = 0;
	float m_delta_pos;
	float m_delta_scale;
	float m_delta_rot;
	//std::vector<Quad> quads;
};

