#include "TexturedVertexBuffer.h"
#include "GraphicsEngine.h"
#include <iostream>

TexturedVertexBuffer::TexturedVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, size_t size_byte_shader)
{
	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size_vertex * size_list;
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_vertices;

	this->m_size_vertex = size_vertex;
	this->m_size_list = size_list;

	ID3D11Device* directXDevice = GraphicsEngine::get()->getd3dDevice();
	HRESULT bufferResult = directXDevice->CreateBuffer(&buff_desc, &init_data, &this->m_buffer);
	if (SUCCEEDED(bufferResult)) {
		std::cout << "Creation of textured buffer succeeded. \n";
	}
	else {
		throw std::exception("TexturedVertexBuffer not created successfully");
	}

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		//semantic name - index, format, input slot, aligned byte offset, input slot class, instance data step rate
		//2 bytes each entry
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	UINT layoutSize = ARRAYSIZE(layout);
	HRESULT layoutResult = directXDevice->CreateInputLayout(layout, layoutSize, shader_byte_code, size_byte_shader, &this->m_layout);
	if (SUCCEEDED(layoutResult)) {
		std::cout << "Creation of input layout succeeded. \n";
	}
	else {
		throw std::exception("InputLayout not created successfully");
	}
}

TexturedVertexBuffer::~TexturedVertexBuffer()
{
	VertexBuffer::~VertexBuffer();
}