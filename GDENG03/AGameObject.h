#pragma once
#include <string>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "AComponent.h"
#include "PhysicsSystem.h"
#include <vector>
#include "reactphysics3d/reactphysics3d.h"

class VertexShader;
class PixelShader;
class EditorAction;

class AGameObject
{
public:
	enum PrimitiveType {
		CAMERA,
		CUBE,
		TEXTURED_CUBE,
		PLANE,
		SPHERE,
		PHYSICS_CUBE,
		PHYSICS_PLANE
	};

	struct AQuaternion {
		float w = 0.0f;
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
	};

	AGameObject(std::string name, PrimitiveType type);
	~AGameObject();

	typedef std::vector<AComponent*> ComponentList;

	PrimitiveType getObjectType();

	virtual void update(double deltaTime) = 0;
	virtual void draw(int width, int height);

	void setPosition(float x, float y, float z);
	void setPosition(Vector3D pos);
	Vector3D getLocalPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	Vector3D getLocalScale();

	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rot);
	Vector3D getLocalRotation();

	bool isEnabled();
	void setEnabled(bool enabled);
	std::string getName();

	void attachComponent(AComponent* component);
	void detachComponent(AComponent* component);

	AComponent* findComponentByName(std::string name);
	AComponent* findComponentByType(AComponent::ComponentType type, std::string);
	ComponentList getComponentsOfType(AComponent::ComponentType type);
	ComponentList getComponentsOfRecursive(AComponent::ComponentType type);

	void recomputeMatrix(float matrix[16]);
	float* getPhysicsLocalMatrix();
	void updateLocalMatrix();
	Matrix4x4 getLocalMatrix();
	float* getRawMatrix();

	virtual void saveEditState();
	virtual void restoreEditState();

	// refactor this so that you could instead use these on both appwindow and gameobject instead of redeclaring their own versions

	struct vertex {
		Vector3D position;
		//Vector3D position1;
		Vector3D color;
		Vector3D color1;
	};

	_declspec(align(16))
		struct constant {
		Matrix4x4 m_world;
		Matrix4x4 m_view;
		Matrix4x4 m_proj;
		float m_time = 0.0f;
	};

protected:
	std::string name;
	Vector3D localPos;
	Vector3D localScale;
	Vector3D localRot;
	AQuaternion orientation;
	Matrix4x4 localMat;
	PrimitiveType objectType;
	ComponentList componentList;
	EditorAction* lastEditState;
	bool enabled = true;
	bool overrideMatrix = false;
};