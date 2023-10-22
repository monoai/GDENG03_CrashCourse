#include "AGameObject.h"

AGameObject::AGameObject(std::string name)
{
	this->name = name;
	this->localRotation = Vector3D(0.0f,0.0f,0.0f);
	this->localPosition = Vector3D(0.0f, 0.0f, 0.0f);
	this->localScale = Vector3D(1.0f, 1.0f, 1.0f);
}

AGameObject::~AGameObject()
{
}

void AGameObject::draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{
}

void AGameObject::setPosition(float x, float y, float z)
{
	this->localPosition = Vector3D(x, y, z);
}

void AGameObject::setPosition(Vector3D pos)
{
	this->localPosition = pos;
}

Vector3D AGameObject::getLocalPosition()
{
	return this->localPosition;
}

void AGameObject::setScale(float x, float y, float z)
{
	this->localScale = Vector3D(x, y, z);
}

void AGameObject::setScale(Vector3D scale)
{
	this->localScale = scale;
}

void AGameObject::setRotation(float x, float y, float z)
{
	this->localRotation = Vector3D(x, y, z);
}

void AGameObject::setRotation(Vector3D rot)
{
	this->localRotation = rot;
}

Vector3D AGameObject::getLocalRotation()
{
	return this->localRotation;
}

Vector3D AGameObject::getLocalScale()
{
	return this->localScale;
}

std::string AGameObject::getName()
{
	return this->name;
}
