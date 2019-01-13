#include "EventListener.hpp"

EventListener::EventListener(Window* w) {
	m_Window = w;
	GLFWwindow* wind = m_Window->m_GLFWwindow;
}

void EventListener::onKey(GLFWwindow* window, int key, int scancode, int action, int modifiers) {
	for (auto& handler : m_Handlers)
		handler->onKey(key, scancode, action, modifiers);
}

void EventListener::onMouseButton(GLFWwindow* window, int button, int action, int modifiers) {
	for (auto& handler : m_Handlers)
		handler->onMouseButton(button, action, modifiers);
}

void EventListener::onCursorPosition(GLFWwindow* window, double xPos, double yPos) {
	for (auto& handler : m_Handlers)
		handler->onCursorPosition(xPos, yPos);
}

void EventListener::onScroll(GLFWwindow* window, double xPos, double yPos) {
	for (auto& handler : m_Handlers)
		handler->onScroll(xPos, yPos);
}


void EventListener::registerHandler(EventHandler* listener) {
	m_Handlers.push_back(listener);
	GlobalGLFWEventHandler::getInstance()->registerWindowListener(this->m_Window, listener);
}

void EventListener::unregisterHandler(EventHandler* listener) {
	m_Handlers.erase(std::remove(m_Handlers.begin(), m_Handlers.end(), listener), m_Handlers.end());
	GlobalGLFWEventHandler::getInstance()->unregisterWindowListener(this->m_Window, listener);
}

EventListener::~EventListener() {

}
