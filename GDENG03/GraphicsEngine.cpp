#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "TexturedVertexBuffer.h"

#include <d3dcompiler.h>
#include <iostream>

GraphicsEngine* GraphicsEngine::m_engine = NULL;

GraphicsEngine::GraphicsEngine()
{
    D3D_DRIVER_TYPE driver_types[] = {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE
    };
    UINT num_driver_types = ARRAYSIZE(driver_types);

    D3D_FEATURE_LEVEL feature_levels[] = {
        D3D_FEATURE_LEVEL_11_0
    };
    UINT num_feature_levels = ARRAYSIZE(feature_levels);

    HRESULT res = 0;

    //ID3D11DeviceContext* m_imm_context;
    for (UINT driver_type_index = 0; driver_type_index < num_driver_types;) {
        res = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels, num_feature_levels, D3D11_SDK_VERSION, &m_d3d_device, &m_feature_level, &m_imm_context);

        if (SUCCEEDED(res)) {
            break;
            ++driver_type_index;
        }

        if (FAILED(res)) {
            throw std::exception("GraphicsEngine not created successfully");
        }
    }

    m_imm_device_context = new DeviceContext(m_imm_context);

    m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device);
    m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
    m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);
}

GraphicsEngine::~GraphicsEngine()
{
    if (m_vs)m_vs->Release();
    if (m_ps)m_ps->Release();

    if (m_vsblob)m_vsblob->Release();
    if (m_psblob)m_psblob->Release();

    m_dxgi_device->Release();
    m_dxgi_adapter->Release();
    m_dxgi_factory->Release();

    delete m_imm_device_context;

    m_d3d_device->Release();
}

void GraphicsEngine::initialize()
{
    m_engine = new GraphicsEngine();
}

SwapChain* GraphicsEngine::createSwapChain(HWND hwnd, UINT width, UINT height)
{
    SwapChain* sc = nullptr;
    try {
        sc = new SwapChain(hwnd, width, height);
    }
    catch (const std::exception& ex) { std::cout << ex.what() << std::endl; }
    return sc;
}

DeviceContext* GraphicsEngine::getImmediateDeviceContext()
{
    return this->m_imm_device_context;
}

TexturedVertexBuffer* GraphicsEngine::createTexturedBuffer(void* vertexList, UINT vertexSize, UINT listSize, void* shaderByteCode, UINT byteShaderSize)
{
    TexturedVertexBuffer* tvb = nullptr;
    try {
        tvb = new TexturedVertexBuffer(vertexList, vertexSize, listSize, shaderByteCode, byteShaderSize);
    }
    catch (const std::exception& ex) { std::cout << ex.what() << std::endl; }
    return tvb;
}

VertexBuffer* GraphicsEngine::createVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, size_t size_byte_shader)
{
    VertexBuffer* vb = nullptr;
    try {
        vb = new VertexBuffer(list_vertices, size_vertex, size_list, shader_byte_code, size_byte_shader);
    }
    catch (const std::exception& ex) { std::cout << ex.what() << std::endl; }
    return vb;
}

IndexBuffer* GraphicsEngine::createIndexBuffer(void* list_indices, UINT size_list)
{
    IndexBuffer* ib = nullptr;
    try {
        ib = new IndexBuffer(list_indices, size_list);
    }
    catch (const std::exception& ex) { std::cout << ex.what() << std::endl; }
    return ib;
}

ConstantBuffer* GraphicsEngine::createConstantBuffer(void* buffer, UINT size_buffer)
{
    ConstantBuffer* cb = nullptr;
    try {
        cb = new ConstantBuffer(buffer, size_buffer);
    }
    catch (const std::exception& ex) { std::cout << ex.what() << std::endl; }
    return cb;
}

VertexShader* GraphicsEngine::createVertexShader(const void* shader_byte_code, size_t byte_code_size)
{
    VertexShader* vs = nullptr;
    try {
        vs = new VertexShader(shader_byte_code, byte_code_size);
    }
    catch (const std::exception& ex) { std::cout << ex.what() << std::endl; }
    return vs;
}

PixelShader* GraphicsEngine::createPixelShader(const void* shader_byte_code, size_t byte_code_size)
{
    PixelShader* ps = nullptr;
    try {
        ps = new PixelShader(shader_byte_code, byte_code_size);
    }
    catch (const std::exception& ex) { std::cout << ex.what() << std::endl; }
    return ps;
}

ID3D11Device* GraphicsEngine::getd3dDevice()
{
    return this->m_d3d_device;
}

bool GraphicsEngine::compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
    ID3DBlob* error_blob = nullptr;
    if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "vs_5_0", 0, 0, &m_blob, &error_blob)))
    {
        if (error_blob) error_blob->Release();
        return false;
    }

    *shader_byte_code = m_blob->GetBufferPointer();
    *byte_code_size = m_blob->GetBufferSize();

    return true;
}

bool GraphicsEngine::compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
    ID3DBlob* error_blob = nullptr;
    if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "ps_5_0", 0, 0, &m_blob, &error_blob)))
    {
        if (error_blob) error_blob->Release();
        return false;
    }

    *shader_byte_code = m_blob->GetBufferPointer();
    *byte_code_size = m_blob->GetBufferSize();

    return true;
}

void GraphicsEngine::releaseCompiledShader()
{
    if (m_blob)m_blob->Release();
}

GraphicsEngine* GraphicsEngine::get()
{
    return m_engine;
}
