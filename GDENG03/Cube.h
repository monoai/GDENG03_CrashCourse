#pragma once
#include "AGameObject.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

class Cube : public AGameObject
{
public:
	Cube(std::string name, void* shaderByteCode, size_t sizeShader);
	~Cube();

	void update(double deltaTime) override;
	void draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) override;
	void setAnimSpeed(float speed);

private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	ConstantBuffer* constantBuffer;
	float ticks = 0.0f;
	float colorTick = 0.0f;
	double deltaTime = 0.0f;
	float speed = 10.0f;
};

