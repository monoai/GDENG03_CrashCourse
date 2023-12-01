#pragma once
#include <d3d11.h>

class DeviceContext;

class ConstantBuffer {
public:
	ConstantBuffer(void* buffer, UINT size_buffer);
	void update(DeviceContext* context, void* buffer);
	~ConstantBuffer();
private:
	ID3D11Buffer* m_buffer;
private:
	friend class DeviceContext;
};