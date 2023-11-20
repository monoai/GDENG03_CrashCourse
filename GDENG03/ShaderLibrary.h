#pragma once
#include <iostream>
#include <unordered_map>
#include <string>

class VertexShader;
class PixelShader;

class ShaderNames {
public:
	//vertex shader names
	const std::wstring BASE_VERTEX_SHADER_NAME = L"VertexShader.hlsl";
	const std::wstring TEXTURED_VERTEX_SHADER_NAME = L"TexturedVertexShader.hlsl";

	//pixel shader names
	const std::wstring BASE_PIXEL_SHADER_NAME = L"PixelShader.hlsl";
	const std::wstring TEXTURED_PIXEL_SHADER_NAME = L"TexturedPixelShader.hlsl";
};

class ShaderLibrary
{
public:
	class ShaderData {
	public:
		void* shader_byte_code = NULL;
		size_t size_shader = 0;
	};

	typedef std::unordered_map<std::wstring, VertexShader*> VertexShaderTable;
	typedef std::unordered_map<std::wstring, PixelShader*> PixelShaderTable;

	static ShaderLibrary* getInstance();
	static void initialize();
	static void destroy();

	void requestVertexShaderData(std::wstring vertexShaderName, void** shader_byte_code, size_t* size_shader); //since shader byte code gets dereferenced for some reason if stored in a hash table. request manually.
	VertexShader* getVertexShader(std::wstring vertexShaderName);
	PixelShader* getPixelShader(std::wstring pixelShaderName);

private:
	ShaderLibrary();
	~ShaderLibrary();
	ShaderLibrary(ShaderLibrary const&) {};             // copy constructor is private
	ShaderLibrary& operator=(ShaderLibrary const&) {};  // assignment operator is private*/
	static ShaderLibrary* sharedInstance;

	VertexShaderTable activeVertexShaders;
	PixelShaderTable activePixelShaders;
};

