#pragma once
#include "AUIScreen.h"
#include <iostream>
#include "GameObjectManager.h"
#include "GraphicsEngine.h"
#include "VertexShader.h"

class ToolbarScreen : public AUIScreen
{
public:
	ToolbarScreen(std::string name);
private:
	virtual void drawUI() override;
};