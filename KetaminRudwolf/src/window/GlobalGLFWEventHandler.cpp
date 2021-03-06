#include "GlobalGLFWEventHandler.hpp"

GlobalGLFWEventHandler* GlobalGLFWEventHandler::instance = nullptr;

GlobalGLFWEventHandler::GlobalGLFWEventHandler() {}

GlobalGLFWEventHandler::~GlobalGLFWEventHandler() {}

void onKey(GLFWwindow* window, int key, int scancode, int action, int modifiers) {
	for (auto& listener : GlobalGLFWEventHandler::getInstance()->m_Listeners) {
		if (window == listener.first->getGLFWWindow()) {
			listener.second->onKey(key, scancode, action, modifiers);
		}
	}
}

void onMouseButton(GLFWwindow* window, int button, int action, int modifiers) {
	for (auto& listener : GlobalGLFWEventHandler::getInstance()->m_Listeners) {
		if (window == listener.first->getGLFWWindow()) {
			listener.second->onMouseButton(button, action, modifiers);
		}
	}
}

void onCursorPosition(GLFWwindow* window, double xPos, double yPos) {
	for (auto& listener : GlobalGLFWEventHandler::getInstance()->m_Listeners) {
		if (window == listener.first->getGLFWWindow()) {
			listener.second->onCursorPosition(xPos, yPos);
		}
	}
}

void onScroll(GLFWwindow* window, double xPos, double yPos) {
	for (auto& listener : GlobalGLFWEventHandler::getInstance()->m_Listeners) {
		if (window == listener.first->getGLFWWindow()) {
			listener.second->onScroll(xPos, yPos);
		}
	}
}

GlobalGLFWEventHandler* GlobalGLFWEventHandler::getInstance() {
	if (instance == nullptr) {
		instance = new GlobalGLFWEventHandler();
	}
	return instance;
}

void GlobalGLFWEventHandler::registerWindowListener(Window* w, EventHandler* h) {
	std::pair<Window*, EventHandler*> pair = std::make_pair(w, h);
	this->m_Listeners.push_back(pair);
	glfwSetKeyCallback(w->m_GLFWwindow, onKey);
	glfwSetMouseButtonCallback(w->m_GLFWwindow, onMouseButton);
	glfwSetCursorPosCallback(w->m_GLFWwindow, onCursorPosition);
	glfwSetScrollCallback(w->m_GLFWwindow, onScroll);
}

void GlobalGLFWEventHandler::unregisterWindowListener(Window* w, EventHandler* h) {
	std::pair<Window*, EventHandler*> pair(w, h);
	this->m_Listeners.erase(std::remove(this->m_Listeners.begin(), this->m_Listeners.end(), pair), this->m_Listeners.end());
}
