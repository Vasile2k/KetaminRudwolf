#include "Game.hpp"

Game* Game::instance = nullptr;

Game::Game() {

	if (!glewInit()) {
		throw new std::runtime_error("Failed to initialize GLEW!");
	}
	if (!glfwInit()) {
		throw new std::runtime_error("Failed to initialize GLFW!");
	}

	m_Window = new Window();
}

Game::~Game() {
	glfwTerminate();
	delete m_Window;
}

Game* Game::getInstance() {
	if (!Game::instance) {
		throw new std::runtime_error("Game is not initialized!");
	}
	return instance;
}

void Game::create() {
	if (Game::instance == nullptr) {
		Game::instance = new Game();
	} else {
		throw new std::runtime_error("Game already created!");
	}
}

void Game::destroy() {
	if (Game::instance) {
		delete Game::instance;
		Game::instance = nullptr;
	}
}

// To test only
class GameHandler : public EventHandler {
	void onKey(int key, int scancode, int action, int modifiers) {
		std::cout << "Pressed key " << key << std::endl;
	}

	void onMouseButton(int button, int action, int modifiers) {
		std::cout << "Pressed button " << button << std::endl;
	}

	void onCursorPosition(double xPos, double yPos) {
		std::cout << "Pos " << xPos << std::endl;
	}

	void onScroll(double xPos, double yPos) {
		std::cout << "Scroll " << xPos << std::endl;
	}

};

int Game::exec() {


	std::cout << "Rudwolf, the dog on da' Key!" << std::endl;

	//m_Window->setFullscreen(true);
	//m_Window->setFullscreen(false);

	m_Window->makeContextCurrent();

	GameHandler* h = new GameHandler();

	m_Window->getEventListener()->registerHandler(h);

	while (!m_Window->shouldClose()) {
		m_Window->pollEvents();
		m_Window->swapBuffers();
	}

	return 0;
}

Window* Game::getWindow() {
	return this->m_Window;
}
