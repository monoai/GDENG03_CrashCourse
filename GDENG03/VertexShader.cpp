#include "VertexShader.h"
#include "GraphicsEngine.h"
#include <exception>
#include <iostream>

VertexShader::VertexShader(const void* shader_byte_code, size_t byte_code_size)
{
	if (FAILED(GraphicsEngine::get()->m_d3d_device->CreateVertexShader(shader_byte_code, byte_code_size, nullptr, &this->m_vs))) {
		throw std::exception("VertexShader not created successfully");
		//std::cout << "VertexShader not created successfully" << std::endl;
	}	
}

ID3D11VertexShader* VertexShader::getShader()
{
	return this->m_vs;
}

VertexShader::~VertexShader() {
	m_vs->Release();
}
