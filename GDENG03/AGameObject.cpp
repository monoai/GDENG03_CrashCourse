#include "AGameObject.h"
#include "EditorAction.h"

AGameObject::AGameObject(std::string name, PrimitiveType type)
{
	this->name = name;
	this->objectType = type;
	this->localRot = Vector3D(0.0f,0.0f,0.0f);
	this->localPos = Vector3D(0.0f, 0.0f, 0.0f);
	this->localScale = Vector3D(1.0f, 1.0f, 1.0f);
	this->localMat.setIdentity();
}

AGameObject::~AGameObject()
{
}

AGameObject::PrimitiveType AGameObject::getObjectType()
{
	return this->objectType;
}

void AGameObject::draw(int width, int height)
{
}

void AGameObject::setPosition(float x, float y, float z)
{
	this->localPos = Vector3D(x, y, z);
	this->overrideMatrix = false;
}

void AGameObject::setPosition(Vector3D pos)
{
	this->localPos = pos;
	this->overrideMatrix = false;
}

Vector3D AGameObject::getLocalPosition()
{
	return this->localPos;
}

void AGameObject::setScale(float x, float y, float z)
{
	this->localScale = Vector3D(x, y, z);
	this->overrideMatrix = false;
}

void AGameObject::setScale(Vector3D scale)
{
	this->localScale = scale;
	this->overrideMatrix = false;
}

void AGameObject::setRotation(float x, float y, float z)
{
	this->localRot = Vector3D(x, y, z);
	this->overrideMatrix = false;
}

void AGameObject::setRotation(Vector3D rot)
{
	this->localRot = rot;
	this->overrideMatrix = false;
}

Vector3D AGameObject::getLocalRotation()
{
	return this->localRot;
}

bool AGameObject::isEnabled()
{
	return this->enabled;
}

void AGameObject::setEnabled(bool enabled)
{
	this->enabled = enabled;
}

Vector3D AGameObject::getLocalScale()
{
	return this->localScale;
}

std::string AGameObject::getName()
{
	return this->name;
}

void AGameObject::attachComponent(AComponent* component)
{
	this->componentList.push_back(component);
	component->attachOwner(this);
}

void AGameObject::detachComponent(AComponent* component)
{
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

AComponent* AGameObject::findComponentByName(std::string name)
{
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getName() == name) {
			return this->componentList[i];
		}
	}

	return NULL;
}

AComponent* AGameObject::findComponentByType(AComponent::ComponentType type, std::string name)
{
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getName() == name && this->componentList[i]->getType() == type) {
			return this->componentList[i];
		}
	}

	return NULL;
}

AGameObject::ComponentList AGameObject::getComponentsOfType(AComponent::ComponentType type)
{
	ComponentList foundList;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getType() == type) {
			foundList.push_back(this->componentList[i]);
		}
	}

	return foundList;
}

AGameObject::ComponentList AGameObject::getComponentsOfRecursive(AComponent::ComponentType type)
{
	ComponentList foundList;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getType() == type) {
			foundList.push_back(this->componentList[i]);
		}
	}

	return foundList;
}

void AGameObject::recomputeMatrix(float matrix[16])
{
	float matrix4x4[4][4];
	matrix4x4[0][0] = matrix[0];
	matrix4x4[0][1] = matrix[1];
	matrix4x4[0][2] = matrix[2];
	matrix4x4[0][3] = matrix[3];

	matrix4x4[1][0] = matrix[4];
	matrix4x4[1][1] = matrix[5];
	matrix4x4[1][2] = matrix[6];
	matrix4x4[1][3] = matrix[7];

	matrix4x4[2][0] = matrix[8];
	matrix4x4[2][1] = matrix[9];
	matrix4x4[2][2] = matrix[10];
	matrix4x4[2][3] = matrix[11];

	matrix4x4[3][0] = matrix[12];
	matrix4x4[3][1] = matrix[13];
	matrix4x4[3][2] = matrix[14];
	matrix4x4[3][3] = matrix[15];

	Matrix4x4 newMat, scaleMat, transMat;
	newMat.setMatrix(matrix4x4); 
	scaleMat.setScale(this->localScale);
	transMat.setTranslation(this->localPos);
	this->localMat = scaleMat.multiply(transMat.multiply(newMat));
	this->overrideMatrix = true;
}

float* AGameObject::getPhysicsLocalMatrix()
{
	Matrix4x4 transMat;
	transMat.setIdentity();

	Matrix4x4 translateMat;
	translateMat.setIdentity();
	translateMat.setTranslation(this->getLocalPosition());

	Matrix4x4 scaleMat;
	scaleMat.setScale(Vector3D(1.0f,1.0f,1.0f));

	Vector3D rotation = this->getLocalRotation();
	Matrix4x4 zMat; zMat.setRotationZ(rotation.getValues().getZ());
	Matrix4x4 xMat; xMat.setRotationX(rotation.getValues().getX());
	Matrix4x4 yMat; yMat.setRotationY(rotation.getValues().getY());

	Matrix4x4 rotMat;
	rotMat.setIdentity();

	rotMat = rotMat.multiply(xMat.multiply(yMat.multiply(zMat)));
	transMat = transMat.multiply(scaleMat.multiply(rotMat));
	transMat = transMat.multiply(translateMat);

	return transMat.getMatrixFloat();
}

void AGameObject::updateLocalMatrix()
{
	Matrix4x4 transMat;
	transMat.setIdentity();

	Matrix4x4 translateMat;
	translateMat.setTranslation(this->getLocalPosition());

	Matrix4x4 scaleMat;
	scaleMat.setScale(this->getLocalScale());

	Vector3D rotation = this->getLocalRotation();
	Matrix4x4 zMat; zMat.setRotationZ(rotation.getValues().getZ());
	Matrix4x4 xMat; xMat.setRotationX(rotation.getValues().getX());
	Matrix4x4 yMat; yMat.setRotationY(rotation.getValues().getY());

	Matrix4x4 rotMat;
	rotMat.setIdentity();

	rotMat = rotMat.multiply(xMat.multiply(yMat.multiply(zMat)));
	transMat = transMat.multiply(scaleMat.multiply(rotMat));
	transMat = transMat.multiply(translateMat);
	this->localMat = transMat;
}

Matrix4x4 AGameObject::getLocalMatrix()
{
	return this->localMat;
}

float* AGameObject::getRawMatrix()
{
	return nullptr;
}

void AGameObject::saveEditState()
{
	if (this->lastEditState == NULL) {
		this->lastEditState = new EditorAction(this);
	}
}

void AGameObject::restoreEditState()
{
	if (this->lastEditState != NULL) {
		this->localPos = this->lastEditState->getStorePos();
		this->localScale = this->lastEditState->getStoredScale();
		this->orientation = this->lastEditState->getStoredOrientation();
		this->localMat = this->lastEditState->getStoredMatrix();
		this->lastEditState = NULL;
		std::cout << "objName: " << this->getName() << std::endl;
		std::cout << "localPos: " << this->localPos.getX() << this->localPos.getY() << this->localPos.getZ() << std::endl;
		std::cout << "localScale: " << this->localScale.getX() << this->localScale.getY() << this->localScale.getZ() << std::endl;
		std::cout << "localPos: " << this->localRot.getX() << this->localRot.getY() << this->localRot.getZ() << std::endl;
		std::cout << "-------" << std::endl;
	}
	else {
		std::cout << "[WARNING] - NULL, no restoration." << std::endl;
	}
}
