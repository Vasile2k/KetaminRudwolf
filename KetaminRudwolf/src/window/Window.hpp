#pragma once
#include <GLFW/glfw3.h>
#include "Common.hpp"
#include "EventListener.hpp"

class Window {

private:

	GLFWwindow* m_GLFWwindow;
	EventListener* m_EventListener;

public:
	Window() : Window(1280, 720, "K") {};
	Window(int width, int height, const char* title, bool fullscreen = false);
	void setResolution(int width, int height);
	void setFullscreen(bool fullscreen);
	int getWidth();
	int getHeight();
	bool getFullscreen();
	void pollEvents();
	bool shouldClose();
	void swapBuffers();
	void makeContextCurrent();
	EventListener* getEventListener();
	GLFWwindow* getGLFWWindow();
	~Window();

	friend class EventListener;
	friend class GlobalGLFWEventHandler;

};
