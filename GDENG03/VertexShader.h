#pragma once
#include <d3d11.h>

class GraphicsEngine;
class DeviceContext;

class VertexShader {
public:
	VertexShader(const void* shader_byte_code, size_t byte_code_size);
	~VertexShader();
	ID3D11VertexShader* getShader();
private:
	ID3D11VertexShader* m_vs;
private:
	friend class GraphicsEngine;
	friend class DeviceContext;
};
