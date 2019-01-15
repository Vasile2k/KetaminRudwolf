#include "Game.hpp"
#include "../render/Renderer.hpp"
#include "../render/GUIRenderer.hpp"
#include "scene/SceneMenu.hpp"

Game* Game::instance = nullptr;

Game::Game() {

	m_Window = new Window();

	m_MenuScene = new SceneMenu(m_CurrentScene);
	m_CurrentScene = m_MenuScene;
}

Game::~Game() {
	glfwTerminate();
	delete m_Window;
	if (m_CurrentScene != m_MenuScene) {
		delete m_CurrentScene;
	}
	delete m_MenuScene;

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

int Game::exec() {


	std::cout << "Rudwolf, the dog on da' Key!" << std::endl;

	m_Window->makeContextCurrent();

	GameHandler* h = new GameHandler();

	m_Window->getEventListener()->registerHandler(h);

	std::chrono::milliseconds currentTime = getCurrentTime();

	while (!m_Window->shouldClose()) {

		if (m_CurrentScene) {
			std::chrono::milliseconds now = getCurrentTime();
			m_CurrentScene->onUpdate(now - currentTime);
			m_CurrentScene->onRender(Renderer::getInstance());
			GUIRenderer::getInstance()->newFrame();
			m_CurrentScene->onGUIRender(GUIRenderer::getInstance());
			GUIRenderer::getInstance()->render();
			currentTime = now;

			if (m_CurrentScene != m_MenuScene) {
				if (m_CurrentScene->isDone()) {
					delete m_CurrentScene;
					m_CurrentScene = m_MenuScene;
				}
			} else {
				if (m_CurrentScene->isDone()) {
					break;
				}
			}

		}

		m_Window->swapBuffers();
		m_Window->pollEvents();
	}

	return 0;
}

Window* Game::getWindow() {
	return this->m_Window;
}

Game::GameHandler::GameHandler() {

}

Game::GameHandler::~GameHandler() {

}

void Game::GameHandler::onKey(int key, int scancode, int action, int modifiers) {
	if (Game::getInstance()->m_CurrentScene) {
		Game::getInstance()->m_CurrentScene->onKey(key, scancode, action, modifiers);
	}
}

void Game::GameHandler::onMouseButton(int button, int action, int modifiers) {
	if (Game::getInstance()->m_CurrentScene) {
		Game::getInstance()->m_CurrentScene->onMouseButton(button, action, modifiers);
	}
}

void Game::GameHandler::onCursorPosition(double xPos, double yPos) {
	if (Game::getInstance()->m_CurrentScene) {
		Game::getInstance()->m_CurrentScene->onCursorPosition(xPos, yPos);
	}
}

void Game::GameHandler::onScroll(double xPos, double yPos) {
	if (Game::getInstance()->m_CurrentScene) {
		Game::getInstance()->m_CurrentScene->onScroll(xPos, yPos);
	}
}

std::chrono::milliseconds getCurrentTime() {
	using namespace std::chrono;
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch());
}
