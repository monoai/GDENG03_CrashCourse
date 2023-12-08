#include "SceneReader.h"
#include <iostream>
#include <fstream>
#include "GameObjectManager.h"

typedef std::fstream FileReader;

SceneReader::SceneReader(std::string directory)
{
	this->directory = directory;
}

SceneReader::~SceneReader()
{
}

std::vector<std::string> SceneReader::split(const std::string& s, char delim) {
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> elems;
	while (std::getline(ss, item, delim)) {
		elems.push_back(std::move(item));
	}
	return elems;
}

void SceneReader::readFromFile()
{
	std::string fileDir = this->directory + ".iet";
	if (this->directory.find(".iet") != std::string::npos) {
		fileDir = this->directory;
	}

	FileReader  sceneFile;
	sceneFile.open(fileDir, std::ios::in);

	int index = 0;
	std::string readLine;

	std::string objectName;
	AGameObject::PrimitiveType objectType;
	Vector3D position;
	Vector3D rotation;
	Vector3D scale;
	bool hasRigidbody = false;
	reactphysics3d::BodyType type{};
	float mass = 0.0f;
	bool gravity = false;
	bool isEnabled = false;
	while (std::getline(sceneFile, readLine)) {
		if (index == 0) {
			objectName = readLine;
			index++;
		}
		else if (index == 1) {
			std::vector stringSplit = split(readLine, ' ');
			objectType = (AGameObject::PrimitiveType)std::stoi(stringSplit[1]);
			index++;
		}
		else if (index == 2) {
			std::vector stringSplit = split(readLine, ' ');
			position = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
			index++;
		}
		else if (index == 3) {
			std::vector stringSplit = split(readLine, ' ');
			rotation = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
			index++;
		}
		else if (index == 4) {
			std::vector stringSplit = split(readLine, ' ');
			scale = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]), std::stof(stringSplit[3]));
			index++;
		}
		else if (index == 5) {
			std::vector stringSplit = split(readLine, ' ');
			hasRigidbody = (bool)std::stoi(stringSplit[1]);
			if (hasRigidbody) {
				index++;
			}
			else {
				index = 0;
				GameObjectManager::getInstance()->createObjectFromFile(objectName, objectType, position, rotation, scale);
			}
		}
		else if (index == 6) {
			std::vector stringSplit = split(readLine, ' ');
			type = (reactphysics3d::BodyType)std::stoi(stringSplit[1]);
			index++;
		}
		else if (index == 7) {
			std::vector stringSplit = split(readLine, ' ');
			mass = std::stof(stringSplit[1]);
			index++;
		}
		else if (index == 8) {
			std::vector stringSplit = split(readLine, ' ');
			gravity = (bool)std::stoi(stringSplit[1]);
			index++;
		}
		else if (index == 9) {
			std::vector stringSplit = split(readLine, ' ');
			isEnabled = (bool)std::stoi(stringSplit[1]);
			index = 0;
			GameObjectManager::getInstance()->createObjectFromFile(objectName, objectType, position, rotation, scale, type, mass, gravity, isEnabled);
		}
	}
}
