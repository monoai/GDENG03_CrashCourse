#pragma once
#include <iostream>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "AGameObject.h"

class EditorAction
{
public:
	EditorAction(AGameObject* gameObject);
	~EditorAction();

	std::string getOwnerName();
	Vector3D getStorePos();
	Vector3D getStoredScale();
	AGameObject::AQuaternion getStoredOrientation();
	Matrix4x4 getStoredMatrix();

private:
	std::string objectName;
	Vector3D localPosition;
	Vector3D localScale;
	AGameObject::AQuaternion orientation;
	Matrix4x4 localMatrix;
};