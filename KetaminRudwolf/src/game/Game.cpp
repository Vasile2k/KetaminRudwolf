#include "Game.hpp"

#include <iostream>
#include <stdexcept>

Game::Game() {

	if (!glewInit()) {
		throw new std::runtime_error("Failed to initialize GLEW!");
	}
	if (!glfwInit()) {
		throw new std::runtime_error("Failed to initialize GLFW!");
	}

	m_Window = new Window();
}

int Game::exec() {


	std::cout << "Rudwolf, the dog on da' Key!" << std::endl;

	//m_Window->setFullscreen(true);
	//m_Window->setFullscreen(false);

	m_Window->makeContextCurrent();

	while (!m_Window->shouldClose()) {
		m_Window->pollEvents();
		m_Window->swapBuffers();
	}

	return 0;
}

Game::~Game() {
	glfwTerminate();
	delete m_Window;
}
