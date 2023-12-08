#include "SceneWriter.h"
#include <iostream>
#include <fstream>
#include "GameObjectManager.h"
#include "PhysicsComponent.h"

typedef std::fstream FileWriter;
SceneWriter::SceneWriter(std::string directory)
{
	this->directory = directory;
}

SceneWriter::~SceneWriter()
{
}

void SceneWriter::writeToFile()
{
	std::string fileDir = this->directory;
	if (this->directory.find(".level") != std::string::npos) {
		fileDir = this->directory;
	}

	FileWriter  sceneFile;
	sceneFile.open(fileDir, std::ios::out);

	std::cout << "Selected filename " << fileDir << "\n";

	GameObjectManager::List allObjects = GameObjectManager::getInstance()->getAllObjects();

	for (int i = 0; i < allObjects.size(); i++) {
		sceneFile << allObjects[i]->getName() << std::endl;
		Vector3D position = allObjects[i]->getLocalPosition();
		Vector3D rotation = allObjects[i]->getLocalRotation();
		Vector3D scale = allObjects[i]->getLocalScale();

		sceneFile << "Type: " << allObjects[i]->getObjectType() << std::endl;
		sceneFile << "Position: " << position.getX() << " " << position.getY() << " " << position.getZ() << std::endl;
		sceneFile << "Rotation: " << rotation.getX() << " " << rotation.getY() << " " << rotation.getZ() << std::endl;
		sceneFile << "Scale: " << scale.getX() << " " << scale.getY() << " " << scale.getZ() << std::endl;
		PhysicsComponent* component = (PhysicsComponent*)allObjects[i]->findComponentByType(AComponent::ComponentType::Physics, "PhysicsComponent_" + allObjects[i]->getName());
		if (component != NULL) {
			sceneFile << "Rigidbody: " << 1 << std::endl;
			sceneFile << "Bodytype: " << (int)component->getRigidBody()->getType() << std::endl;
			sceneFile << "Mass: " << component->getRigidBody()->getMass() << std::endl;
			sceneFile << "Gravity: " << component->getRigidBody()->isGravityEnabled() << std::endl;
			sceneFile << "IsEnabled: " << component->getRigidBody()->isActive() << std::endl;
		}
		else {
			sceneFile << "Rigidbody: " << 0 << std::endl;
		}
	}
	sceneFile.close();
}