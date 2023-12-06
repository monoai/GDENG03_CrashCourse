#include "GameObjectManager.h"
#include "EngineTime.h"
#include "Cube.h"
#include "TexturedCube.h"
#include "Plane.h"
#include "PhysicsCube.h"
#include "PhysicsPlane.h"
#include "AGameObject.h"

GameObjectManager* GameObjectManager::sharedInstance = NULL;

void GameObjectManager::applyEditorAction(EditorAction* action)
{
	AGameObject* object = this->findObjectByName(action->getOwnerName());
	if (object != NULL) {
		object->recomputeMatrix(action->getStoredMatrix().getMatrixFloat());
		object->setPosition(action->getStorePos());
		object->setRotation(action->getStoredOrientation().x, action->getStoredOrientation().y, action->getStoredOrientation().z);
		object->setScale(action->getStoredScale());

	}
}

void GameObjectManager::saveEditStates()
{
	for (int i = 0; i < this->objList.size(); i++) {
		this->objList[i]->saveEditState();
	}
}

void GameObjectManager::restoreEditStates()
{
	for (int i = 0; i < this->objList.size(); i++) {
		this->objList[i]->restoreEditState();
	}
}

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

std::string GameObjectManager::checkName(std::string name)
{
	if (this->objMap[name] != NULL) {
		int count = 1;
		std::string revisedString = name + " " + "(" + std::to_string(count) + ")";
		while (this->objMap[revisedString] != NULL) {
			count++;
			revisedString = name + " " + "(" + std::to_string(count) + ")";
		}
		name = revisedString;
		return name;
	}
	else {
		return name;
	}
}

void GameObjectManager::createObject(AGameObject::PrimitiveType type)
{
	if (type == AGameObject::PrimitiveType::CUBE) {
		Cube* cube = new Cube(checkName("Cube"));
		cube->setPosition(0.0f, 0.0f, 0.0f);
		cube->setScale(1.0f, 1.0f, 1.0f);
		this->addObject(cube);
	}

	else if (type == AGameObject::PrimitiveType::TEXTURED_CUBE) {
		TexturedCube* cube = new TexturedCube(checkName("Cube_Textured"));
		cube->setPosition(0.0f, 0.0f, 0.0f);
		cube->setScale(1.0f, 1.0f, 1.0f);
		this->addObject(cube);
	}

	else if (type == AGameObject::PrimitiveType::PLANE) {
		Plane* plane = new Plane(checkName("Plane"));
		this->addObject(plane);
	}

	else if (type == AGameObject::PrimitiveType::PHYSICS_CUBE) {
		PhysicsCube* cube = new PhysicsCube(checkName("Cube_Physics"));
		this->addObject(cube);
	}

	else if (type == AGameObject::PrimitiveType::PHYSICS_PLANE) {
		PhysicsPlane* plane = new PhysicsPlane(checkName("Plane_Physics"));
		this->addObject(plane);
	}
}

void GameObjectManager::createObjectFromFile(std::string name, AGameObject::PrimitiveType type, Vector3D position, Vector3D rotation, Vector3D scale)
{
	if (type == AGameObject::PrimitiveType::CUBE) {
		Cube* cube = new Cube(name);
		cube->setPosition(position);
		cube->setRotation(rotation);
		cube->setScale(scale);
		this->addObject(cube);
	}

	else if (type == AGameObject::PrimitiveType::PLANE) {
		Plane* plane = new Plane(name);
		plane->setPosition(position);
		plane->setRotation(rotation);
		plane->setScale(scale);
		this->addObject(plane);
	}

	else if (type == AGameObject::PrimitiveType::TEXTURED_CUBE) {
		TexturedCube* cube = new TexturedCube(name);
		cube->setPosition(position);
		cube->setRotation(rotation);
		cube->setScale(scale);
		this->addObject(cube);
	}

	else if (type == AGameObject::PrimitiveType::PHYSICS_CUBE) {
		PhysicsCube* cube = new PhysicsCube(name);
		cube->setPosition(position);
		cube->setRotation(rotation);
		cube->setScale(scale);
		this->addObject(cube);
	}

	else if (type == AGameObject::PrimitiveType::PHYSICS_PLANE) {
		PhysicsPlane* plane = new PhysicsPlane(name);
		plane->setPosition(position);
		plane->setRotation(rotation);
		plane->setScale(scale);
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
		std::cout << "selected " << this->objMap[name]->getName() << std::endl;
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
