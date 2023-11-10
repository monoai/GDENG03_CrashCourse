#pragma once
#include "AGameObject.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

class Cube : public AGameObject
{
public:
	Cube(std::string name, void* shader_byte_code, size_t size_shader);
	~Cube();

	void update(double deltaTime) override;
	void draw(int width, int height, VertexShader* m_vs, PixelShader* m_ps) override;
	void setAnimSpeed(float speed);

private:
	VertexBuffer* m_vb;
	IndexBuffer* m_ib;
	ConstantBuffer* m_cb;
	float ticks = 0.0f;
	float colorTick = 0.0f;
	double deltaTime = 0.0f;
	float speed = 10.0f;
};

