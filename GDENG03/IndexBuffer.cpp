#include "IndexBuffer.h"
#include "GraphicsEngine.h"
#include <exception>

IndexBuffer::IndexBuffer(void* list_indices, UINT size_list) : m_buffer(0)
{
	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = 4 * size_list;
	buff_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_indices;

	m_size_list = size_list;

	if (FAILED(GraphicsEngine::get()->m_d3d_device->CreateBuffer(&buff_desc, &init_data, &m_buffer)))
	{
		throw std::exception("IndexBuffer not created successfully");
	}
}

UINT IndexBuffer::getSizeIndexList()
{
	return this->m_size_list;
}

ID3D11Buffer* IndexBuffer::getBuffer()
{
	return this->m_buffer;
}

IndexBuffer::~IndexBuffer()
{
	m_buffer->Release();
}
