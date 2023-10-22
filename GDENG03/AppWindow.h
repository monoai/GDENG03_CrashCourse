#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "InputListener.h"
#include "Cube.h"
#include <vector>

struct vertex {
	Vector3D position;
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

class AppWindow: public Window, public InputListener
{
public:
	AppWindow();

	//void update();

	~AppWindow();
	
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onKillFocus() override;

	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point mouse_pos) override;

	virtual void onLeftMouseDown(const Point mouse_pos) override;
	virtual void onLeftMouseUp(const Point mouse_pos) override;
	virtual void onRightMouseDown(const Point mouse_pos) override;
	virtual void onRightMouseUp(const Point mouse_pos) override;
private:
	SwapChain* m_swap_chain;
	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;
	IndexBuffer* m_ib;

	std::vector<Cube*> cubeList;

	//unsigned long m_old_time = 0;
	//float m_delta_time = 0;
	bool reverse = false;
	float speedFactor = 1.0f;
	float m_angle = 0;
	float m_delta_pos;
	float m_delta_scale;
	float m_delta_rot;
	float m_delta_time;

	/* // from following the tutorial
	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;
	float m_scale_cube = 1;
	float m_forward = 0.0f;
	float m_rightward = 0.0f;
	Matrix4x4 m_world_cam;
	*/

	//bool rmouseClick = false;
	//std::vector<Quad> quads;
};

