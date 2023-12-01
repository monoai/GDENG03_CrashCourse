#pragma once
#include "Cube.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

class Plane : public Cube
{
public:
	Plane(std::string name, bool skipInit = false);
	~Plane();

	void update(double deltaTime) override;

};