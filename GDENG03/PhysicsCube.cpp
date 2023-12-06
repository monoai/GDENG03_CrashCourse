#include "PhysicsCube.h"
#include "PhysicsComponent.h"

PhysicsCube::PhysicsCube(std::string name, bool skipInit) : Cube(name, skipInit)
{
	this->objectType = PrimitiveType::PHYSICS_CUBE;
	this->setPosition(0.0f, 0.0f, 0.0f);
	this->setScale(1.0f, 1.0f, 1.0f);
	this->updateLocalMatrix();
	this->component = new PhysicsComponent("PhysicsComponent_" + this->getName(), this);
	this->attachComponent(this->component);
}

PhysicsCube::~PhysicsCube()
{
	Cube::~Cube();
}

void PhysicsCube::update(double deltaTime)
{
	//std::cout << "gravity? " << this->component->getRigidBody()->isGravityEnabled() << std::endl;
}
