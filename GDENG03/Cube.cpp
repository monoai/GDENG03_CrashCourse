#include "Cube.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "SceneCameraHandler.h"
#include "InputSystem.h"
#include "ShaderLibrary.h"

Cube::Cube(std::string name, bool skipInit) : AGameObject(name)
{
	if (skipInit)
		return;

	ShaderNames shaderNames;
	void* shader_byte_code = NULL;
	size_t size_shader = 0;
	ShaderLibrary::getInstance()->requestVertexShaderData(shaderNames.BASE_VERTEX_SHADER_NAME, &shader_byte_code, &size_shader);

	vertex quadList[] = {
		//FRONT FACE
		{Vector3D(-0.75f,-0.75f,-0.75f),    Vector3D(1.0f,0.0f,1.0f),  Vector3D(1.0f,0.0f,0.0f) },
		{Vector3D(-0.75f,0.75f,-0.75f),    Vector3D(0.0f,0.0f,1.0f),  Vector3D(1.0f,0.0f,0.0f) },
		{Vector3D(0.75f,0.75f,-0.75f), Vector3D(1.0f,0.0f,1.0f),  Vector3D(1.0f,0.0f,0.0f) },
		{Vector3D(0.75f,-0.75f,-0.75f), Vector3D(0.0f,0.0f,1.0f),  Vector3D(1.0f,0.0f,0.0f) },

		//BACK FACE
		{Vector3D(0.75f,-0.75f,0.75f),    Vector3D(1.0f,0.0f,1.0f),  Vector3D(1.0f,0.0f,0.0f) },
		{Vector3D(0.75f,0.75f,0.75f),    Vector3D(0.0f,0.0f,1.0f),  Vector3D(1.0f,0.0f,0.0f) },
		{Vector3D(-0.75f,0.75f,0.75f),   Vector3D(1.0f,0.0f,1.0f),  Vector3D(1.0f,0.0f,0.0f) },
		{Vector3D(-0.75f,-0.75f,0.75f),     Vector3D(0.0f,0.0f,1.0f),  Vector3D(1.0f,0.0f,0.0f) },
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
	//this->ticks += deltaTime;

	//float rotFactor = this->ticks * this->speed;
	//this->setRotation(rotFactor, rotFactor, rotFactor);
}

void Cube::draw(int width, int height)
{
	GraphicsEngine* graphEngine = GraphicsEngine::get();
	DeviceContext* deviceContext = graphEngine->getImmediateDeviceContext();

	//set vertex shader and pixel shader for the object
	ShaderNames shaderNames;
	deviceContext->setRenderConfig(ShaderLibrary::getInstance()->getVertexShader(shaderNames.BASE_VERTEX_SHADER_NAME), ShaderLibrary::getInstance()->getPixelShader(shaderNames.BASE_PIXEL_SHADER_NAME));

	constant cc;

	if (this->overrideMatrix)
	{
		cc.m_world = this->localMat;
	}
	else
	{
		this->updateLocalMatrix();
		cc.m_world = this->localMat;
	}

	Matrix4x4 cameraMatrix = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();
	cc.m_view = cameraMatrix;

	//cc.m_view.setIdentity();
	//cc.m_proj.setOrthoLH(width / 400.0f, height / 400.0f, -4.0f, 4.0f);
	cc.m_proj.setPerspectiveFovLH((float)width / (float)height, (float)width / (float)height, 0.1f, 1000.0f);

	//colorTick += (float)(this->deltaTime) * 0.5f;
	//cc.m_time = (float)colorTick;
	//std::cout << "colorTick: " << colorTick << std::endl;
	//std::cout << "cc time: " << cc.m_time << std::endl;
	//std::cout << "dT: " << this->deltaTime << std::endl;

	this->m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(this->m_cb);
	
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(this->m_ib);
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(this->m_vb);
	
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(this->m_ib->getSizeIndexList(), 0, 0);
}

void Cube::setAnimSpeed(float speed)
{
	this->speed = speed;
}
