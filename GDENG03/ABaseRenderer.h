#pragma once
#include "TextureManager.h"

class ABaseRenderer
{
public:
	enum RendererType { 
		DEFAULT = 0, 
		TEXTURE = 1, 
		MATERIAL = 2 
	};
	ABaseRenderer(RendererType rendererType);
	virtual ~ABaseRenderer();
	virtual void setMaterialPath(std::string path);
	std::string getMaterialPath() const;
	virtual void configureDeviceContext() const = 0;
	RendererType getRendererType();

protected:
	RendererType rendererType;
	std::string materialPath;
};