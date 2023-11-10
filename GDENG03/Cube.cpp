#include "Cube.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "SceneCameraHandler.h"
#include "InputSystem.h"

Cube::Cube(std::string name, void* shader_byte_code, size_t size_shader) : AGameObject(name)
{
	vertex quadList[] = {
		//FRONT FACE
		{Vector3D(-0.75f,-0.75f,-0.75f), Vector3D(-0.75f,-0.75f,-0.75f),    Vector3D(1.0f,0.0f,1.0f),  Vector3D(1.0f,0.0f,0.0f) },
		{Vector3D(-0.75f,0.75f,-0.75f), Vector3D(-0.75f,0.75f,-0.75f),    Vector3D(0.0f,0.0f,1.0f),  Vector3D(1.0f,0.0f,0.0f) },
		{Vector3D(0.75f,0.75f,-0.75f), Vector3D(0.75f,0.75f,-0.75f), Vector3D(1.0f,0.0f,1.0f),  Vector3D(1.0f,0.0f,0.0f) },
		{Vector3D(0.75f,-0.75f,-0.75f), Vector3D(0.75f,-0.75f,-0.75f), Vector3D(0.0f,0.0f,1.0f),  Vector3D(1.0f,0.0f,0.0f) },

		//BACK FACE
		{Vector3D(0.75f,-0.75f,0.75f),Vector3D(0.75f,-0.75f,0.75f),    Vector3D(1.0f,0.0f,1.0f),  Vector3D(1.0f,0.0f,0.0f) },
		{Vector3D(0.75f,0.75f,0.75f),Vector3D(0.75f,0.75f,0.75f),    Vector3D(0.0f,0.0f,1.0f),  Vector3D(1.0f,0.0f,0.0f) },
		{Vector3D(-0.75f,0.75f,0.75f),Vector3D(-0.75f,0.75f,0.75f),   Vector3D(1.0f,0.0f,1.0f),  Vector3D(1.0f,0.0f,0.0f) },
		{Vector3D(-0.75f,-0.75f,0.75f),Vector3D(-0.75f,-0.75f,0.75f),     Vector3D(0.0f,0.0f,1.0f),  Vector3D(1.0f,0.0f,0.0f) },
	};

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
	this->m_ib = GraphicsEngine::get()->createIndexBuffer();
	this->m_ib->load(indexList, ARRAYSIZE(indexList));

	constant cc;
	cc.m_time = 0.0f;
	this->m_cb = GraphicsEngine::get()->createConstantBuffer();
	this->m_cb->load(&cc, sizeof(constant));
}

Cube::~Cube()
{
	this->m_vb->release();
	this->m_ib->release();
	AGameObject::~AGameObject();
}

void Cube::update(double deltaTime)
{
	this->deltaTime = deltaTime;
	this->ticks += deltaTime;

	//float rotFactor = this->ticks * this->speed;
	//this->setRotation(rotFactor, rotFactor, rotFactor);
}

void Cube::draw(int width, int height, VertexShader* m_vs, PixelShader* m_ps)
{
	constant cc;

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
	cc.m_world = transMat;

	Matrix4x4 cameraMatrix = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();
	cc.m_view = cameraMatrix;

	//cc.m_view.setIdentity();
	//cc.m_proj.setOrthoLH(width / 400.0f, height / 400.0f, -4.0f, 4.0f);
	cc.m_proj.setPerspectiveFovLH((float)width / (float)height, (float)width / (float)height, 0.1f, 1000.0f);

	colorTick += (float)(this->deltaTime) * 0.5f;
	cc.m_time = (float)colorTick;
	//std::cout << "colorTick: " << colorTick << std::endl;
	//std::cout << "cc time: " << cc.m_time << std::endl;
	//std::cout << "dT: " << this->deltaTime << std::endl;

	this->m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, this->m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, this->m_cb);
	
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(this->m_ib);
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(this->m_vb);
	
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(this->m_ib->getSizeIndexList(), 0, 0);
}

void Cube::setAnimSpeed(float speed)
{
	this->speed = speed;
}
