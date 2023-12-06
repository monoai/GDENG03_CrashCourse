#pragma once
#include "Cube.h"

class PhysicsCube : public Cube
{
public:
	PhysicsCube(std::string name, bool skipInit = false);
	~PhysicsCube();

	void update(double deltaTime) override;

protected:
	float mass = 3.0f;
	PhysicsComponent* component;
};