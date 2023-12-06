#include "ABaseRenderer.h"

ABaseRenderer::ABaseRenderer(RendererType rendererType)
{
	this->rendererType = rendererType;
}

ABaseRenderer::~ABaseRenderer()
{

}

void ABaseRenderer::setMaterialPath(std::string path)
{
	this->materialPath = path;
}

std::string ABaseRenderer::getMaterialPath() const
{
	return this->materialPath;
}

ABaseRenderer::RendererType ABaseRenderer::getRendererType()
{
	return this->rendererType;
}