#include "ShaderLibrary.h"
#include "GraphicsEngine.h"
#include "VertexShader.h"
#include "PixelShader.h"

ShaderLibrary* ShaderLibrary::sharedInstance = NULL;

ShaderLibrary* ShaderLibrary::getInstance()
{
	return sharedInstance;
}

void ShaderLibrary::initialize()
{
	sharedInstance = new ShaderLibrary();
}

void ShaderLibrary::destroy()
{
	delete sharedInstance;
}

void ShaderLibrary::requestVertexShaderData(std::wstring vertexShaderName, void** shader_byte_code, size_t* size_shader)
{
	GraphicsEngine* graphEngine = GraphicsEngine::get();
	graphEngine->compileVertexShader(vertexShaderName.c_str(), "vsmain", shader_byte_code, size_shader);
}

VertexShader* ShaderLibrary::getVertexShader(std::wstring vertexShaderName)
{
	if (this->activeVertexShaders[vertexShaderName] == NULL) {
		std::cout << "Vertex shader " << vertexShaderName.c_str() << " not found. Have you initialized it? \n";
	}
	return this->activeVertexShaders[vertexShaderName];
}

PixelShader* ShaderLibrary::getPixelShader(std::wstring pixelShaderName)
{
	if (this->activePixelShaders[pixelShaderName] == NULL) {
		std::cout << "Pixel shader " << pixelShaderName.c_str() << " not found. Have you initialized it? \n";
	}
	return this->activePixelShaders[pixelShaderName];
}

ShaderLibrary::ShaderLibrary()
{
	//initialize and load all shaders for use
	GraphicsEngine* graphEngine = GraphicsEngine::get();

	ShaderNames shaderNames;
	ShaderData shaderData;
	graphEngine->compileVertexShader(shaderNames.BASE_VERTEX_SHADER_NAME.c_str(), "vsmain", &shaderData.shader_byte_code, &shaderData.size_shader);
	this->activeVertexShaders[shaderNames.BASE_VERTEX_SHADER_NAME] = graphEngine->createVertexShader(shaderData.shader_byte_code, shaderData.size_shader);

	graphEngine->compilePixelShader(shaderNames.BASE_PIXEL_SHADER_NAME.c_str(), "psmain", &shaderData.shader_byte_code, &shaderData.size_shader);
	this->activePixelShaders[shaderNames.BASE_PIXEL_SHADER_NAME] = graphEngine->createPixelShader(shaderData.shader_byte_code, shaderData.size_shader);

	graphEngine->compileVertexShader(shaderNames.TEXTURED_VERTEX_SHADER_NAME.c_str(), "main", &shaderData.shader_byte_code, &shaderData.size_shader);
	this->activeVertexShaders[shaderNames.TEXTURED_VERTEX_SHADER_NAME] = graphEngine->createVertexShader(shaderData.shader_byte_code, shaderData.size_shader);

	graphEngine->compilePixelShader(shaderNames.TEXTURED_PIXEL_SHADER_NAME.c_str(), "main", &shaderData.shader_byte_code, &shaderData.size_shader);
	this->activePixelShaders[shaderNames.TEXTURED_PIXEL_SHADER_NAME] = graphEngine->createPixelShader(shaderData.shader_byte_code, shaderData.size_shader);

	std::cout << "Shader library initialized. \n";
}

ShaderLibrary::~ShaderLibrary()
{
	ShaderNames shaderNames;
	this->activeVertexShaders[shaderNames.BASE_VERTEX_SHADER_NAME]->release();
	this->activePixelShaders[shaderNames.BASE_PIXEL_SHADER_NAME]->release();

	this->activeVertexShaders.clear();
	this->activePixelShaders.clear();
}
