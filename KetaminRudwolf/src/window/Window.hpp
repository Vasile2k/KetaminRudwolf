#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class Window {

private:

	GLFWwindow* m_GLFWwindow;

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
	~Window();

};
