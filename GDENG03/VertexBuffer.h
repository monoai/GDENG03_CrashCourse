#pragma once
#include <d3d11.h>

class DeviceContext;

class VertexBuffer
{
public:
	VertexBuffer() = default;
	VertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, size_t size_byte_shader);
	UINT getSizeVertexList();
	~VertexBuffer();
protected:
	UINT m_size_vertex;
	UINT m_size_list;
protected:
	ID3D11Buffer* m_buffer;
	ID3D11InputLayout* m_layout;
protected:
	friend class DeviceContext;
};