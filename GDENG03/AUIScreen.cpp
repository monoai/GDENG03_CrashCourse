#include "AUIScreen.h"

AUIScreen::AUIScreen(std::string name) {
	this->name = name;
	UIManager::getInstance()->pushList(name, this);
}

AUIScreen::~AUIScreen()
{

}

std::string AUIScreen::getName()
{
	return this->name;
}

void AUIScreen::SetEnabled(bool flag)
{
	this->enabled = flag;
}
