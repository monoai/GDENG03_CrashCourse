#include "SceneReader.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include "GameObjectManager.h"

constexpr inline double pi = 3.14159265358979323846;

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
	std::string fileDir = this->directory;
	if (this->directory.find(".unity") != std::string::npos) {
		fileDir = this->directory;
		u2lparser(fileDir);
		return;
	}
	else {
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
		std::cout << "line: " << readLine << std::endl;
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

void SceneReader::u2lparser(std::string fileDir)
{
	std::cout << "this is a unity level" << std::endl;
	FileReader  sceneFile;
	sceneFile.open(fileDir, std::ios::in);

	bool done = false;
	std::string readLine;

	bool readObj = false;
	std::string objectName;
	AGameObject::PrimitiveType objectType;
	Vector3D position;
	Vector3D rotation;
	Vector3D scale;
	bool hasRigidbody = false;
	float mass = 0.0f;
	reactphysics3d::BodyType type{};
	bool gravity = false;
	bool isEnabled = true;
	while (std::getline(sceneFile, readLine)) {
		//std::cout << "line: " << readLine << std::endl;
		//std::vector stringSplit = split(readLine, ' ');
		if (readLine == "GameObject:") {
			readObj = true;
			hasRigidbody = false;
			done = false;
		}
		if (readObj) {
			if (readLine.find("m_Name:") != std::string::npos) {
				std::vector stringSplit = split(readLine, ' ');
				std::cout << "name: " << stringSplit[3] << std::endl;
				if (stringSplit[3] != "Cube" && stringSplit[3] != "Plane") {
					readObj = false;
					continue;
				}
				else if (stringSplit[3] == "Cube") {
					objectType = AGameObject::PrimitiveType::CUBE;
				}
				else if (stringSplit[3] == "Plane") {
					objectType = AGameObject::PrimitiveType::PLANE;
				}
				objectName = stringSplit[3];
			}
			if (readLine.find("Rigidbody:") != std::string::npos) {
				hasRigidbody = true;
				if (objectName == "Cube") {
					objectType = AGameObject::PrimitiveType::PHYSICS_CUBE;
				}
				else if (objectName == "Plane") {
					objectType = AGameObject::PrimitiveType::PHYSICS_PLANE;
				}
				//std::cout << objectName << " has rigidbody" << std::endl;
			}
			if (hasRigidbody) {
				if (readLine.find("m_Mass:") != std::string::npos) {
					std::vector stringSplit = split(readLine, ' ');
					std::cout << "mass: " << std::stof(stringSplit[3]) << std::endl;
					mass = std::stof(stringSplit[3]);
				}
				if (readLine.find("m_UseGravity:") != std::string::npos) {
					std::vector stringSplit = split(readLine, ' ');
					std::cout << "gravity: " << (bool)std::stoi(stringSplit[3]) << std::endl;
					gravity = (bool)std::stoi(stringSplit[3]);
				}
				if (readLine.find("m_IsKinematic:") != std::string::npos) {
					std::vector stringSplit = split(readLine, ' ');
					std::cout << "isKinematic: " << (bool)std::stoi(stringSplit[3]) << std::endl;
					if ((bool)std::stoi(stringSplit[3]) == true) {
						type = reactphysics3d::BodyType::KINEMATIC;
					}
					else {
						type = reactphysics3d::BodyType::DYNAMIC;
					}
				}
			}
			if (readLine.find("Transform:") != std::string::npos) {
				std::cout << objectName << " has transform" << std::endl;
			}
			if (readLine.find("m_LocalPosition:") != std::string::npos) {
				std::vector stringSplit = split(readLine, ' ');
				std::cout << "localPosition: " << std::stof(stringSplit[4]) << std::stof(stringSplit[6]) << std::stof(stringSplit[8]) << std::endl;
				position = Vector3D(std::stof(stringSplit[4]), std::stof(stringSplit[6]), std::stof(stringSplit[8]));
			}
			if (readLine.find("m_LocalScale:") != std::string::npos) {
				std::vector stringSplit = split(readLine, ' ');
				std::cout << "localScale: " << std::stof(stringSplit[4]) << std::stof(stringSplit[6]) << std::stof(stringSplit[8]) << std::endl;
				scale = Vector3D(std::stof(stringSplit[4]), std::stof(stringSplit[6]), std::stof(stringSplit[8]));
				if (objectName == "Plane") {
					scale = Vector3D(std::stof(stringSplit[4])*10, 0.2f, std::stof(stringSplit[8]) * 10);
				}
			}
			if (readLine.find("m_LocalEulerAnglesHint:") != std::string::npos) {
				std::vector stringSplit = split(readLine, ' ');
				std::cout << "rotation: " << std::stof(stringSplit[4]) << std::stof(stringSplit[6]) << std::stof(stringSplit[8]) << std::endl;
				rotation = Vector3D(std::stof(stringSplit[4])*(pi/180), std::stof(stringSplit[6]) * (pi / 180), std::stof(stringSplit[8]) * (pi / 180));
				done = true;
			}
			if (done && hasRigidbody) {
				std::cout << objectName << " has rigidbody" << std::endl;
				GameObjectManager::getInstance()->createObjectFromFile(objectName, objectType, position, rotation, scale, type, mass, gravity, isEnabled);
				done = false;
			}
			else if (done && hasRigidbody == false) {
				std::cout << objectName << " doesnt have rigidbody" << std::endl;
				GameObjectManager::getInstance()->createObjectFromFile(objectName, objectType, position, rotation, scale);
				done = false;
			}
		}
	}
}
