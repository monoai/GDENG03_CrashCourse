#pragma once
#include <d3d11.h>

class GraphicsEngine;
class DeviceContext;

class PixelShader {
public:
	PixelShader(const void* shader_byte_code, size_t byte_code_size);
	~PixelShader();
	ID3D11PixelShader* getShader();
private:
	ID3D11PixelShader* m_ps;
private:
	friend class GraphicsEngine;
	friend class DeviceContext;
};