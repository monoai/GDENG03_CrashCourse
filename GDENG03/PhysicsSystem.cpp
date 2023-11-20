#include "PhysicsSystem.h"
#include "PhysicsComponent.h"
#include <iostream>
#include "EngineTime.h"

PhysicsSystem::PhysicsSystem()
{
	std::cout << "Loading Physics System. \n";
	this->physicsCommon = new reactphysics3d::PhysicsCommon();
	reactphysics3d::PhysicsWorld::WorldSettings settings;
	settings.defaultVelocitySolverNbIterations = 50;
	settings.gravity = reactphysics3d::Vector3(0, -9.81, 0);
	this->physicsWorld = this->physicsCommon->createPhysicsWorld(settings);
	std::cout << "Successfully created physics world. \n";
}

PhysicsSystem::~PhysicsSystem()
{
	delete this->physicsCommon;
}

void PhysicsSystem::registerComponent(PhysicsComponent* component)
{
	std::cout << "Registering Physics component: " << component->getName() << "\n";
	this->componentTable[component->getName()] = component;
	this->componentList.push_back(component);
}

void PhysicsSystem::unregisterComponent(PhysicsComponent* component)
{
	std::cout << "Unregistering Physics component: " << component->getName() << "\n";

	if (this->componentTable[component->getName()] != NULL) {
		this->componentTable.erase(component->getName());
		int index = -1;
		for (int i = 0; i < this->componentList.size(); i++) {
			if (this->componentList[i] == component) {
				index = i;
				break;
			}
		}

		if (index != -1) {
			this->componentList.erase(this->componentList.begin() + index);
		}
	}
	else {
		std::cout << "Component " << component->getName() << " not registered in physics component. \n";
	}
}

void PhysicsSystem::unregisterComponentByName(std::string name)
{
	if (this->componentTable[name] != NULL) {
		this->unregisterComponent(this->componentTable[name]);
	}
}

PhysicsComponent* PhysicsSystem::findComponentByName(std::string name)
{
	if (this->componentTable[name] == NULL) {
		std::cout << "Component " << name << " not registered in physics component. \n";
	}

	return this->componentTable[name];
}

PhysicsSystem::ComponentList PhysicsSystem::getAllComponents()
{
	return this->componentList;
}

void PhysicsSystem::updateAllComponents()
{
	if (EngineTime::getDeltaTime() > 0.0f) {
		this->physicsWorld->update(EngineTime::getDeltaTime());
		for (int i = 0; i < this->componentList.size(); i++) {
			this->componentList[i]->perform(EngineTime::getDeltaTime());
		}
	}
}

reactphysics3d::PhysicsWorld* PhysicsSystem::getPhysicsWorld()
{
	return this->physicsWorld;
}

reactphysics3d::PhysicsCommon* PhysicsSystem::getPhysicsCommon()
{
	return this->physicsCommon;
}

