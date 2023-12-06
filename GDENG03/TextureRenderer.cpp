#include "TextureRenderer.h"
#include "ShaderLibrary.h"
#include "DeviceContext.h"
#include "GraphicsEngine.h"

TextureRenderer::TextureRenderer() : ABaseRenderer(RendererType::TEXTURE)
{
	//i could do something like load default no texture here or something
}

TextureRenderer::~TextureRenderer()
{
	ABaseRenderer::~ABaseRenderer();
}

void TextureRenderer::setMaterialPath(std::string path)
{
	ABaseRenderer::setMaterialPath(path);

	//convert to wchar format	
	std::string textureString = this->materialPath;
	std::wstring widestr = std::wstring(textureString.begin(), textureString.end());
	const wchar_t* texturePath = widestr.c_str();

	this->texture = static_cast<Texture*>(TextureManager::getInstance()->createTextureFromFile(texturePath));
}

std::string TextureRenderer::getMaterialPath() const
{
	return this->materialPath;
}

Texture* TextureRenderer::getTexture() const
{
	return this->texture;
}

void TextureRenderer::configureDeviceContext() const
{
	DeviceContext* deviceContext = GraphicsEngine::get()->getImmediateDeviceContext();

}