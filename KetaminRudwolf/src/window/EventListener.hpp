#pragma once
#include "Common.hpp"
#include "Window.hpp"
#include "EventHandler.hpp"
#include "GlobalGLFWEventHandler.hpp"

class EventListener {

private:

	Window* m_Window;
	std::vector<EventHandler*> m_Handlers;

public:

	EventListener(Window* w);
	void onKey(GLFWwindow* window, int key, int scancode, int action, int modifiers);
	void onMouseButton(GLFWwindow* window, int button, int action, int modifiers);
	void onCursorPosition(GLFWwindow* window, double xPos, double yPos);
	void onScroll(GLFWwindow* window, double xPos, double yPos);
	void registerHandler(EventHandler* listener);
	void unregisterHandler(EventHandler* listener);
	~EventListener();

	friend class GlobalGLFWEventHandler;

};
