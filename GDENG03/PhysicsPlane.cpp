#include "PhysicsPlane.h"
#include "PhysicsComponent.h"
#include "GraphicsEngine.h"
#include "ShaderLibrary.h"
#include "PhysicsSystem.h"

PhysicsPlane::PhysicsPlane(std::string name, bool skipInit) : Cube(name, skipInit)
{
	ShaderNames shaderNames;
	void* shader_byte_code = NULL;
	size_t size_shader = 0;
	ShaderLibrary::getInstance()->requestVertexShaderData(shaderNames.BASE_VERTEX_SHADER_NAME, &shader_byte_code, &size_shader);

	//override cube constructor with different renderer
	//create buffers for drawing. vertex data that needs to be drawn are temporarily placed here.
	vertex quadList[] = {
		//X, Y, Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,1,1),  Vector3D(0.2f,0,0) },
		{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,1), Vector3D(0.2f,0.2f,0) },
		{Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,1),  Vector3D(0.2f,0.2f,0) },
		{Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,1,1), Vector3D(0.2f,0,0) },

		//BACK FACE
		{Vector3D(0.5f,-0.5f,0.5f),    Vector3D(1,1,1), Vector3D(0,0.2f,0) },
		{Vector3D(0.5f,0.5f,0.5f),    Vector3D(1,1,1), Vector3D(0,0.2f,0.2f) },
		{Vector3D(-0.5f,0.5f,0.5f),   Vector3D(1,1,1),  Vector3D(0,0.2f,0.2f) },
		{Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(1,1,1), Vector3D(0,0.2f,0) },
	};

	//this->m_vb->release();
	this->m_vb = GraphicsEngine::get()->createVertexBuffer();
	this->m_vb->load(quadList, sizeof(vertex), ARRAYSIZE(quadList), shader_byte_code, size_shader);

	unsigned int indexList[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};

	this->m_ib->release();
	this->m_ib = GraphicsEngine::get()->createIndexBuffer();
	this->m_ib->load(indexList, ARRAYSIZE(indexList));

	this->m_cb->release();
	//create constant buffer
	constant cc;
	cc.m_time = 0;
	this->m_cb = GraphicsEngine::get()->createConstantBuffer();
	this->m_cb->load(&cc, sizeof(cc));

	this->setPosition(0.0f, -5.0f, 0.0f);
	this->setScale(32.0f, 0.2f, 32.0f);
	this->setRotation(0.0f, 0.0f, 0.0f);
	this->updateLocalMatrix();
	this->attachComponent(new PhysicsComponent("PhysicsComponent", this));

	PhysicsComponent* component = (PhysicsComponent*)this->findComponentByType(AComponent::ComponentType::Physics, "PhysicsComponent");
	component->getRigidBody()->setType(reactphysics3d::BodyType::KINEMATIC);
	//component->getRigidBody()->setMass(0.0f);
}

PhysicsPlane::~PhysicsPlane()
{
}