#pragma once
#include "PhysicsCube.h"

class PhysicsPlane : public Cube
{
public:
	PhysicsPlane(std::string name, bool skipInit = false);
	~PhysicsPlane();
};