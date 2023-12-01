#include "PixelShader.h"
#include "GraphicsEngine.h"
#include <exception>

PixelShader::PixelShader(const void* shader_byte_code, size_t byte_code_size)
{
	if (FAILED(GraphicsEngine::get()->m_d3d_device->CreatePixelShader(shader_byte_code, byte_code_size, nullptr, &m_ps)))
		throw std::exception("PixelShader not created successfully");
}

ID3D11PixelShader* PixelShader::getShader()
{
	return this->m_ps;
}

PixelShader::~PixelShader()
{
	m_ps->Release();
}