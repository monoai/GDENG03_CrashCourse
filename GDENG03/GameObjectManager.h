#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "AGameObject.h"
#include "EditorAction.h"

class GameObjectManager
{
public:
	typedef std::vector<AGameObject*> List;
	typedef std::unordered_map<std::string, AGameObject*> HashTable;

	void applyEditorAction(EditorAction* action);
	void saveEditStates();
	void restoreEditStates();

	static GameObjectManager* getInstance();
	static void initialize();
	static void destroy();

	AGameObject* findObjectByName(std::string name);
	List getAllObjects();
	int activeObjects();
	void updateAll();
	void renderAll(int vp_width, int vp_height);
	void addObject(AGameObject* gameObject);
	std::string checkName(std::string name);
	void createObject(AGameObject::PrimitiveType type);
	void createObjectFromFile(std::string name, AGameObject::PrimitiveType type, Vector3D position, Vector3D rotation, Vector3D scale);
	void deleteObject(AGameObject* gameObject);
	void deleteObjectByName(std::string name);
	void setSelectedObject(std::string name);
	void setSelectedObject(AGameObject* gameObject);
	AGameObject* getSelectedObject();

private:
	GameObjectManager();
	~GameObjectManager();
	GameObjectManager(GameObjectManager const&) {};
	GameObjectManager& operator=(GameObjectManager const&) {};
	static GameObjectManager* sharedInstance;

	HashTable objMap;
	List objList;

	AGameObject* selectedObject = NULL;
};