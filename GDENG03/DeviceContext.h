#pragma once
#include <d3d11.h>
#include "imgui.h"

class SwapChain;
class VertexBuffer;
class IndexBuffer;
class ConstantBuffer;
class VertexShader;
class PixelShader;
class Texture;

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* device_context);
	void clearRenderTargetColor(SwapChain* swap_chain, float red, float green, float blue, float alpha);
	void clearRenderTargetColor(SwapChain* swap_chain, ImVec4 color);
	void setVertexBuffer(VertexBuffer* vertex_buffer);
	void setIndexBuffer(IndexBuffer* index_buffer);

	void setRenderConfig(VertexShader* vertexShader, PixelShader* pixelShader);

	void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location);
	void drawTriangleStrip(UINT vertex_count, UINT start_vertex_index);
	void setViewportSize(UINT width, UINT height);

	void setVertexShader(VertexShader* vertex_shader);
	void setPixelShader(PixelShader* pixel_shader);

	void setConstantBuffer(ConstantBuffer* buffer);
	void setTexture(Texture* texture);
	~DeviceContext();
public:
	ID3D11DeviceContext* getDeviceContext();
private:
	ID3D11DeviceContext* m_device_context;
private:
	friend class ConstantBuffer;
};

