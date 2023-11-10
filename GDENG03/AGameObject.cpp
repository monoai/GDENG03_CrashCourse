#include "AGameObject.h"

AGameObject::AGameObject(std::string name)
{
	this->name = name;
	this->localRot = Vector3D(0.0f,0.0f,0.0f);
	this->localPos = Vector3D(0.0f, 0.0f, 0.0f);
	this->localScale = Vector3D(1.0f, 1.0f, 1.0f);
}

AGameObject::~AGameObject()
{
}

void AGameObject::draw(int width, int height, VertexShader* m_vs, PixelShader* m_ps)
{
}

void AGameObject::setPosition(float x, float y, float z)
{
	this->localPos = Vector3D(x, y, z);
}

void AGameObject::setPosition(Vector3D pos)
{
	this->localPos = pos;
}

Vector3D AGameObject::getLocalPosition()
{
	return this->localPos;
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
	this->localRot = Vector3D(x, y, z);
}

void AGameObject::setRotation(Vector3D rot)
{
	this->localRot = rot;
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
