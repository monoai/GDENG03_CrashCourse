#include "Cube.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"

Cube::Cube(std::string name, void* shaderByteCode, size_t sizeShader) : GameObject(name)
{
	vertex quadList[] = {
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0),  Vector3D(1.0f,0,0) },
		{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,0), Vector3D(1.0f,1.0f,0) },
		{Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0),  Vector3D(1.0f,1.0f,0) },
		{Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,0), Vector3D(1.0f,0,0) },

		//BACK FACE
		{Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,1,0), Vector3D(0,1.0f,0) },
		{Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,1,1), Vector3D(0,1.0f,1.0f) },
		{Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,1,1),  Vector3D(0,1.0f,1.0f) },
		{Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,1,0), Vector3D(0,1.0f,0) },
	};

	this->vertexBuffer = GraphicsEngine::get()->createVertexBuffer();
	this->vertexBuffer->load(quadList, sizeof(vertex), ARRAYSIZE(quadList), shaderByteCode, sizeShader);

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
	this->indexBuffer = GraphicsEngine::get()->createIndexBuffer();
	this->indexBuffer->load(indexList, ARRAYSIZE(indexList));

	constant cc = {};
	cc.time = 0;
	this->constantBuffer = GraphicsEngine::get()->createConstantBuffer();
	this->constantBuffer->load(&cc, sizeof(constant));
}

Cube::~Cube()
{
	this->vertexBuffer->release();
	this->indexBuffer->release();
	GameObject::~GameObject();
}

void Cube::update(float deltaTime)
{
	this->deltaTime = deltaTime;
	this->ticks += deltaTime;

	float rotSpeed = this->ticks * this->speed;
	this->setRotation(rotSpeed, rotSpeed, rotSpeed);
}

void Cube::draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{
	constant cc = {};

	if (this->deltaPos > 1.0f) {
		this->deltaPos = 0.0f;
	}
	else {
		this->deltaPos += this->deltaTime * 0.1f;
	}

	Matrix4x4 transMat;
	transMat.setIdentity();

	Matrix4x4 translateMat;
	translateMat.setTranslation(this->getLocalPosition());

	Matrix4x4 scaleMat;
	scaleMat.setScale(this->getLocalScale());

	Vector3D rotation = this->getLocalRotation();
	Matrix4x4 zMat; zMat.setRotationZ(rotation.getValues().m_z);
	Matrix4x4 xMat; xMat.setRotationX(rotation.getValues().m_x);
	Matrix4x4 yMat; yMat.setRotationY(rotation.getValues().m_y);

	Matrix4x4 rotMat;
	rotMat.setIdentity();
	rotMat = rotMat.multiply(xMat.multiply(yMat.multiply(zMat)));
	transMat = transMat.multiply(scaleMat.multiply(rotMat));
	transMat = transMat.multiply(translateMat);
	cc.m_world = transMat;

	cc.m_view.setIdentity();
	cc.m_proj.setOrthoLH(width / 400.0f, height / 400.0f, -4.0f, 4.0f);

	this->constantBuffer->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(vertexShader, this->constantBuffer);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(pixelShader, this->constantBuffer);
	
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(this->vertexBuffer);
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(this->indexBuffer);
	
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(this->indexBuffer->getSizeIndexList(), 0, 0);
}

void Cube::setAnimSpeed(float speed)
{
	this->speed = speed;
}
