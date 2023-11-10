#include "Camera.h"
#include "InputSystem.h"

Camera::Camera(std::string name) : AGameObject(name)
{
	this->setPosition(0.0f, 0.0f, -4.0f);
	this->updateViewMatrix();
	InputSystem::getInstance()->addListener(this);
}

Camera::~Camera()
{
	InputSystem::getInstance()->removeListener(this);
}

void Camera::update(double deltaTime)
{
	Vector3D localPos = this->getLocalPosition();
	float x = localPos.getX();
	float y = localPos.getY();
	float z = localPos.getZ();
	float moveSpeed = 10.0f;

	if (InputSystem::getInstance()->isKeyDown('W')) {
		z += (float)deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	} else if (InputSystem::getInstance()->isKeyDown('S')) {
		z -= (float)deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	} else if (InputSystem::getInstance()->isKeyDown('A')) {
		x -= (float)deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	} else if (InputSystem::getInstance()->isKeyDown('D')) {
		x += (float)deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		//std::cout << "x: " << x << std::endl;
		this->updateViewMatrix();
	} else if (InputSystem::getInstance()->isKeyDown('Q')) {
		y -= (float)deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	} else if (InputSystem::getInstance()->isKeyDown('E')) {
		y += (float)deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		//std::cout << "y: " << y << std::endl;
		this->updateViewMatrix();
	}
}

Matrix4x4 Camera::getViewMatrix()
{
	return this->localMat;
}

void Camera::onKeyDown(int key)
{
}

void Camera::onKeyUp(int key)
{
}

void Camera::onMouseMove(const Point deltaPos)
{
	if (this->rmouseClick) {
		Vector3D localRot = this->getLocalRotation();
		float x = localRot.getX();
		float y = localRot.getY();
		float z = localRot.getZ();

		float speed = 0.005f;
		x += deltaPos.getY() * speed;
		y += deltaPos.getX() * speed;

		this->setRotation(x, y, z);
		this->updateViewMatrix();
	}
}

void Camera::onLeftMouseDown(const Point deltaPos)
{
}

void Camera::onLeftMouseUp(const Point deltaPos)
{
}

void Camera::onRightMouseDown(const Point deltaPos)
{
	this->rmouseClick = true;
}

void Camera::onRightMouseUp(const Point deltaPos)
{
	this->rmouseClick = false;
}

void Camera::updateViewMatrix()
{
	Matrix4x4 worldCam;
	worldCam.setIdentity();
	
	Matrix4x4 temp;
	temp.setIdentity();

	Vector3D localRot = this->getLocalRotation();

	temp.setRotationX(localRot.getX());
	worldCam = worldCam.multiply(temp);

	temp.setRotationY(localRot.getY());
	worldCam = worldCam.multiply(temp);

	temp.setTranslation(this->getLocalPosition());
	worldCam = worldCam.multiply(temp);

	worldCam.inverse();
	this->localMat = worldCam;
}
