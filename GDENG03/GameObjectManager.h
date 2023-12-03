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

	enum PrimitiveType {
		CUBE,
		TEXTURED_CUBE,
		PLANE,
		SPHERE,
		PHYSICS_CUBE,
		PHYSICS_PLANE
	};

	static GameObjectManager* getInstance();
	static void initialize();
	static void destroy();

	AGameObject* findObjectByName(std::string name);
	List getAllObjects();
	int activeObjects();
	void updateAll();
	void renderAll(int vp_width, int vp_height);
	void addObject(AGameObject* gameObject);
	void createObject(PrimitiveType type);
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