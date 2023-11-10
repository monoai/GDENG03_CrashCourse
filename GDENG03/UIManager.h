#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "Window.h"
#include "AUIScreen.h"

class AUIScreen;

class UINames {
public:
	const std::string PROFILER_SCREEN = "PROFILER_SCREEN";
	const std::string MENU_SCREEN = "MENU_SCREEN";
	const std::string INSPECTOR_SCREEN = "INSPECTOR_SCREEN";
	const std::string HIERARCHY_SCREEN = "HIERARCHY_SCREEN";
};

class UIManager
{
public:
	typedef std::vector<AUIScreen*> UIList;
	typedef std::unordered_map<std::string, AUIScreen*> UITable;

	static UIManager* getInstance();
	static void initialize(HWND m_hwnd);
	static void destroy();

	void drawAllUI();
	void pushList(AUIScreen* screen);

	static const int WINDOW_WIDTH = 1280;
	static const int WINDOW_HEIGHT = 720;

private:
	UIManager(HWND m_hwnd);
	~UIManager();
	UIManager(UIManager const&) {};
	UIManager& operator=(UIManager const&) {};
	static UIManager* sharedInstance;

	UIList uiList;
	UITable uiTable;
};