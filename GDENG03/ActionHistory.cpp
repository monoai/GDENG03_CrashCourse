#include "ActionHistory.h"
#include "EditorAction.h"
#include "EngineBackend.h"
#include "ActionMemento.h"

ActionHistory* ActionHistory::sharedInstance = NULL;

ActionHistory* ActionHistory::getInstance()
{
	return sharedInstance;
}

void ActionHistory::initialize()
{
	sharedInstance = new ActionHistory();
}

void ActionHistory::destroy()
{
	delete sharedInstance;
}

void ActionHistory::startRecordAction(AGameObject* gameObject)
{
	this->currentGameObject = gameObject;
	oldEditorAction = new EditorAction(gameObject);
}

void ActionHistory::endRecordAction()
{
	EditorAction* newEditorAction = new EditorAction(this->currentGameObject);
	ActionMemento* actionmemento = new ActionMemento(oldEditorAction, newEditorAction);
	this->actionsPerformed.push(actionmemento);

	std::cout << "acting upon: " << this->currentGameObject->getName() << std::endl;
	this->currentGameObject = nullptr;
}

bool ActionHistory::hasRemainingUndoActions()
{
	return !this->actionsPerformed.empty();
}

bool ActionHistory::hasRemainingRedoActions()
{
	return !this->actionsCancelled.empty();
}

EditorAction* ActionHistory::undoAction()
{
	if (this->hasRemainingUndoActions()) {
		ActionMemento* action = this->actionsPerformed.top();
		this->actionsPerformed.pop();
		this->actionsCancelled.push(action);
		return action->getOldAction();
	}
}

EditorAction* ActionHistory::redoAction()
{
	if (this->hasRemainingRedoActions()) {
		ActionMemento* action = this->actionsCancelled.top();
		this->actionsCancelled.pop();
		this->actionsPerformed.push(action);
		return action->getNewAction();
	}
}

void ActionHistory::clear()
{
}

ActionHistory::ActionHistory()
{
}

ActionHistory::~ActionHistory()
{
}
