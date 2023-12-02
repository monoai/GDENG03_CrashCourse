#include "ActionMemento.h"
#include "EditorAction.h"

ActionMemento::ActionMemento(EditorAction* oldAction, EditorAction* newAction)
{
	this->oldAction = oldAction;
	this->newAction = newAction;
}

ActionMemento::~ActionMemento()
{
	this->oldAction = nullptr;
	this->newAction = nullptr;
}

EditorAction* ActionMemento::getOldAction()
{
	return this->oldAction;
}

EditorAction* ActionMemento::getNewAction()
{
	return this->newAction;
}

std::string ActionMemento::getOwnerName()
{
	return this->newAction->getOwnerName();
}
