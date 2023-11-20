#include "GameObjectManager.h"
#include "EngineTime.h"
#include "Cube.h"
#include "Plane.h"
#include "PhysicsCube.h"
#include "PhysicsPlane.h"
#include "AGameObject.h"

GameObjectManager* GameObjectManager::sharedInstance = NULL;

GameObjectManager* GameObjectManager::getInstance()
{
	return sharedInstance;
}

void GameObjectManager::initialize()
{
	sharedInstance = new GameObjectManager();
}

void GameObjectManager::destroy()
{
	sharedInstance->objMap.clear();
	sharedInstance->objList.clear();
	sharedInstance->selectedObject = NULL;
	delete sharedInstance;
}

AGameObject* GameObjectManager::findObjectByName(std::string name)
{
	if (this->objMap[name] != NULL) {
		return this->objMap[name];
	} else {
		std::cout << name << " does not exist";
		return NULL;
	}
}

GameObjectManager::List GameObjectManager::getAllObjects()
{
	return this->objList;
}

int GameObjectManager::activeObjects()
{
	return (size_t)this->objList.size();
}

void GameObjectManager::updateAll()
{
	for (unsigned int i = 0; i < this->objList.size(); i++) {
		if (this->objList[i]->isEnabled()) {
			this->objList[i]->update(EngineTime::getDeltaTime());
		}
	}
}

void GameObjectManager::renderAll(int vp_width, int vp_height)
{
	for (unsigned int i = 0; i < this->objList.size(); i++) {
		if (this->objList[i]->isEnabled()) {
			this->objList[i]->draw(vp_width, vp_height);
		}
	}
}

void GameObjectManager::addObject(AGameObject* gameObject)
{
	this->objMap[gameObject->getName()] = gameObject;
	this->objList.push_back(gameObject);
}

void GameObjectManager::createObject(PrimitiveType type)
{
	if (type == PrimitiveType::CUBE) {
		Cube* cube = new Cube("Cube");
		cube->setPosition(0.0f, 0.0f, 0.0f);
		cube->setScale(1.0f, 1.0f, 1.0f);
		this->addObject(cube);
	}

	else if (type == PrimitiveType::PLANE) {
		Plane* plane = new Plane("Plane");
		this->addObject(plane);
	}

	else if (type == PrimitiveType::PHYSICS_CUBE) {
		PhysicsCube* cube = new PhysicsCube("Cube_Physics");
		this->addObject(cube);
	}

	else if (type == PrimitiveType::PHYSICS_PLANE) {
		PhysicsPlane* plane = new PhysicsPlane("Plane_Physics");
		this->addObject(plane);
	}
}

void GameObjectManager::deleteObject(AGameObject* gameObject)
{
	this->objMap.erase(gameObject->getName());

	int index = -1;
	for (unsigned int i = 0; i < this->objList.size(); i++) {
		if (this->objList[i] == gameObject) {
			index = i;
			break;
		}
	}

	if (index != -1) {
		this->objList.erase(this->objList.begin() + index);
	}

	delete gameObject;
}

void GameObjectManager::deleteObjectByName(std::string name)
{
	AGameObject* object = this->findObjectByName(name);

	if (object != NULL) {
		this->deleteObject(object);
	}
}

void GameObjectManager::setSelectedObject(std::string name)
{
	if (this->objMap[name] != NULL) {
		this->setSelectedObject(this->objMap[name]);
		std::cout << "selected " << this->objMap[name] << std::endl;
	}
}

void GameObjectManager::setSelectedObject(AGameObject* gameObject)
{
	this->selectedObject = gameObject;
}

AGameObject* GameObjectManager::getSelectedObject()
{
	return this->selectedObject;
}

GameObjectManager::GameObjectManager()
{
}


GameObjectManager::~GameObjectManager()
{
}
