#include "PhysicsCube.h"
#include "PhysicsComponent.h"

PhysicsCube::PhysicsCube(std::string name, bool skipInit) : Cube(name, skipInit)
{
	this->setPosition(0.0f, 0.0f, 0.0f);
	this->setScale(1.0f, 1.0f, 1.0f);
	this->updateLocalMatrix();
	this->component = new PhysicsComponent("PhysicsComponent_" + this->name, this);
	this->attachComponent(this->component);
}

PhysicsCube::~PhysicsCube()
{
	Cube::~Cube();
}

void PhysicsCube::update(double deltaTime)
{
	Cube::update(deltaTime);
}

void PhysicsCube::draw(int width, int height)
{
	Cube::draw(width, height);
}

void PhysicsCube::saveEditState()
{
	AGameObject::saveEditState();
}

void PhysicsCube::restoreEditState()
{
	AGameObject::restoreEditState();
	this->detachComponent(this->component);
	delete this->component;

	this->component = new PhysicsComponent("PhysicsComponent_" + this->name, this);
	this->attachComponent(this->component);
}
