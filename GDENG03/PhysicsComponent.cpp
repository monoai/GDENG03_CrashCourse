#include "PhysicsComponent.h"
#include <iostream>
#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
#include "AGameObject.h"
#include "Vector3D.h"
#include "AComponent.h"

PhysicsComponent::PhysicsComponent(std::string name, AGameObject* owner) : AComponent(name, AComponent::ComponentType::Physics, owner)
{
	PhysicsSystem* physicsSystem = BaseComponentSystem::getInstance()->getPhysicsSystem();
	physicsSystem->registerComponent(this);
	reactphysics3d::PhysicsCommon* physicsCommon = physicsSystem->getPhysicsCommon();
	reactphysics3d::PhysicsWorld* physicsWorld = physicsSystem->getPhysicsWorld();

	// Create a rigid body in the world
	Vector3D scale = this->getOwner()->getLocalScale();
	reactphysics3d::Transform transform;
	transform.setFromOpenGL(this->getOwner()->getPhysicsLocalMatrix());
	reactphysics3d::BoxShape* boxShape = physicsCommon->createBoxShape(reactphysics3d::Vector3(scale.getX()/2, scale.getY()/2, scale.getZ()/2));
	this->rigidBody = physicsWorld->createRigidBody(transform);
	this->rigidBody->addCollider(boxShape, transform);
	this->rigidBody->updateMassPropertiesFromColliders();
	//this->rigidBody->setLocalCenterOfMass(reactphysics3d::Vector3(scale.getX()/2, scale.getY()/2, scale.getZ()/2));
	this->rigidBody->setMass(this->mass);
	this->rigidBody->setType(reactphysics3d::BodyType::DYNAMIC);

	transform = this->rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	this->getOwner()->recomputeMatrix(matrix);
}

PhysicsComponent::~PhysicsComponent()
{
	BaseComponentSystem::getInstance()->getPhysicsSystem()->unregisterComponent(this);
	BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsWorld()->destroyRigidBody(this->rigidBody);
	AComponent::~AComponent();
}

void PhysicsComponent::perform(float deltaTime)
{
	const reactphysics3d::Transform transform = this->rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	this->getOwner()->recomputeMatrix(matrix);
	//std::cout << "Owner is: " << this->getOwner()->getName() << "Component: " << this->name << std::endl;
}

reactphysics3d::RigidBody* PhysicsComponent::getRigidBody()
{
	return this->rigidBody;
}