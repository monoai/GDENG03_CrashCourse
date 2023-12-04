#include "Plane.h"
#include "GraphicsEngine.h"
#include "ShaderLibrary.h"

Plane::Plane(std::string name, bool skipInit) : Cube(name, skipInit)
{
	this->objectType = PrimitiveType::PHYSICS_PLANE;
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

	delete this->m_vb;
	this->m_vb = GraphicsEngine::get()->createVertexBuffer(quadList, sizeof(vertex), ARRAYSIZE(quadList), shader_byte_code, size_shader);

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

	delete this->m_ib;
	this->m_ib = GraphicsEngine::get()->createIndexBuffer(indexList, ARRAYSIZE(indexList));

	delete this->m_cb;
	//create constant buffer
	constant cc;
	cc.m_time = 0;
	this->m_cb = GraphicsEngine::get()->createConstantBuffer(&cc, sizeof(cc));

	this->setScale(8.0f, 0.2f, 8.0f);
	this->setRotation(0.0f, 0.0f, 0.0f);
	this->updateLocalMatrix();
}

Plane::~Plane()
{
}

void Plane::update(double deltaTime)
{
	Cube::update(deltaTime);
}