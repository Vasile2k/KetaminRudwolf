#pragma once
#include <utility>
#include <vector>
#include "Common.hpp"
#include "Window.hpp"
#include "EventHandler.hpp"

class GlobalGLFWEventHandler {

private:
	static GlobalGLFWEventHandler* instance;
	std::vector<std::pair<Window*, EventHandler*>> m_Listeners;
	~GlobalGLFWEventHandler();
	GlobalGLFWEventHandler();

public:
	static GlobalGLFWEventHandler* getInstance();
	void registerWindowListener(Window* w, EventHandler* h);
	void unregisterWindowListener(Window* w, EventHandler* h);

	friend void onKey(GLFWwindow* window, int key, int scancode, int action, int modifiers);
	friend void onMouseButton(GLFWwindow* window, int button, int action, int modifiers);
	friend void onCursorPosition(GLFWwindow* window, double xPos, double yPos);
	friend void onScroll(GLFWwindow* window, double xPos, double yPos);
};

