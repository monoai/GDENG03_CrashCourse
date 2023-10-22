#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>
#include "InputListener.h"
#include "Point.h"

class InputSystem
{
public:
	static InputSystem* getInstance();
	static void initialize();
	static void destroy();

	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);
	void update();

	bool isKeyDown(int key);
	bool isKeyUp(int key);

private:
	static InputSystem* sharedInstance;

	void callOnKeyDown(int key);
	void callOnKeyUp(int key);

	void callOnMouseMove(Point deltaPt);
	void callOnLeftMouseDown(Point deltaPt);
	void callOnLeftMouseUp(Point deltaPt);
	void callOnRightMouseDown(Point deltaPt);
	void callOnRightMouseUp(Point deltaPt);

	std::vector<InputListener*> inputListenerList;

	unsigned char keyStates[256] = {};
	unsigned char oldKeyStates[256] = {};

	InputSystem();
	~InputSystem();
	InputSystem(InputSystem const&) {};
	InputSystem& operator=(InputSystem const&) {};

	Point oldMousePos;
	bool firstTimeCall = true;

};

