#include "Window.hpp"

Window::Window(int width, int height, const char* title, bool fullscreen) {

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_GLFWwindow = glfwCreateWindow(width, height, title, fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);

	if (!m_GLFWwindow) {
		throw new std::runtime_error("Failed to create window!");
	}

	this->m_EventListener = new EventListener(this);

}

void Window::setResolution(int width, int height) {
	glfwSetWindowSize(m_GLFWwindow, width, height);
}

void Window::setFullscreen(bool fullscreen) {
	// If we have to change state
	if (this->getFullscreen() != fullscreen) {
		if (fullscreen) {

			GLFWmonitor *monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode *vidMode = glfwGetVideoMode(monitor);
			glfwSetWindowMonitor(m_GLFWwindow, monitor, 0, 0, vidMode->width, vidMode->height, vidMode->refreshRate);

		} else {

			int width;
			int height;
			glfwGetWindowSize(m_GLFWwindow, &width, &height);
			glfwSetWindowMonitor(m_GLFWwindow, fullscreen ? glfwGetPrimaryMonitor() : NULL, 0, 0, width, height, GLFW_DONT_CARE);

		}
	}
}

int Window::getWidth() {
	int width;
	glfwGetWindowSize(m_GLFWwindow, &width, nullptr);
	return width;
}

int Window::getHeight() {
	int height;
	glfwGetWindowSize(m_GLFWwindow, nullptr, &height);
	return height;
}

bool Window::getFullscreen() {
	return glfwGetWindowMonitor(m_GLFWwindow) != nullptr;
}

void Window::pollEvents() {
	glfwPollEvents();
}

bool Window::shouldClose() {
	return glfwWindowShouldClose(m_GLFWwindow);
}

void Window::swapBuffers() {
	glfwSwapBuffers(m_GLFWwindow);
}

void Window::makeContextCurrent() {
	glfwMakeContextCurrent(m_GLFWwindow);
}

EventListener* Window::getEventListener() {
	return m_EventListener;
}

GLFWwindow* Window::getGLFWWindow() {
	return this->m_GLFWwindow;
}

Window::~Window() {
	glfwDestroyWindow(m_GLFWwindow);
	delete m_EventListener;
}
