#pragma once
#include <iostream>
#include <vector>
#include <stack>

class ActionMemento;
class EditorAction;
class AGameObject;
class ActionHistory
{
public:
	typedef std::stack<ActionMemento*> ActionStack;
	static ActionHistory* getInstance();
	static void initialize();
	static void destroy();

	void startRecordAction(AGameObject* gameObject);
	void endRecordAction();
	bool hasRemainingUndoActions();
	bool hasRemainingRedoActions();
	EditorAction* undoAction();
	EditorAction* redoAction();
	void clear();

private:
	ActionHistory();
	~ActionHistory();
	ActionHistory(ActionHistory const&) {};
	ActionHistory& operator=(ActionHistory const&) {};

	static ActionHistory* sharedInstance;

	AGameObject* currentGameObject;
	EditorAction* oldEditorAction;

	ActionStack actionsPerformed;
	ActionStack actionsCancelled;
};