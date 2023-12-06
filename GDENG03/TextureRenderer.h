#pragma once
#include "TextureManager.h"
#include "ABaseRenderer.h"

class TextureRenderer : public ABaseRenderer
{
public:
	TextureRenderer();
	~TextureRenderer();
	void setMaterialPath(std::string path);
	std::string getMaterialPath() const;
	Texture* getTexture() const;
	void configureDeviceContext() const;

private:
	Texture* texture;
};