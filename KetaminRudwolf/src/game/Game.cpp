#include "Game.hpp"
#include "../render/Renderer.hpp"
#include "../render/GUIRenderer.hpp"
#include "scene/SceneMenu.hpp"

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

Game* Game::instance = nullptr;

Game::Game() {

	m_Window = new Window();

	m_MenuScene = new SceneMenu(m_CurrentScene);
	m_CurrentScene = m_MenuScene;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		throw new std::runtime_error("Failed to init SDL!");
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	HWND hwnd = glfwGetWin32Window(m_Window->getGLFWWindow());

	m_SDLWindow = SDL_CreateWindowFrom((void*)hwnd);

	if (m_SDLWindow == nullptr) {
		throw new std::runtime_error("Failed to create SDL_Window!");
	}

}

Game::~Game() {
	SDL_Quit();
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

		if (m_CurrentScene->requireClearing()) {
			m_Window->swapBuffers();
		}
		m_Window->pollEvents();
	}

	return 0;
}

int Game::getJumpKey() {
	return m_JumpKey;
}

int Game::getCrouchKey() {
	return m_CrouchKey;
}

void Game::setJumpKey(int key) {
	this->m_JumpKey = key;
}

void Game::setCrouchKey(int key) {
	this->m_CrouchKey = key;
}

Window* Game::getWindow() {
	return this->m_Window;
}

SDL_Window* Game::getSDLWindow() {
	return this->m_SDLWindow;
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

const char* getKeyName(int key) {
	switch (key) {
		case -1:
			return "UNKNOWN";
		case 32:
			return "SPACE";
		case 39:
			return "APOSTROPHE";
		case 44:
			return "COMMA";
		case 45:
			return "MINUS";
		case 46:
			return "PERIOD";
		case 47:
			return "SLASH";
		case 48:
			return "0";
		case 49:
			return "1";
		case 50:
			return "2";
		case 51:
			return "3";
		case 52:
			return "4";
		case 53:
			return "5";
		case 54:
			return "6";
		case 55:
			return "7";
		case 56:
			return "8";
		case 57:
			return "9";
		case 59:
			return "SEMICOLON";
		case 61:
			return "EQUAL";
		case 65:
			return "A";
		case 66:
			return "B";
		case 67:
			return "C";
		case 68:
			return "D";
		case 69:
			return "E";
		case 70:
			return "F";
		case 71:
			return "G";
		case 72:
			return "H";
		case 73:
			return "I";
		case 74:
			return "J";
		case 75:
			return "K";
		case 76:
			return "L";
		case 77:
			return "M";
		case 78:
			return "N";
		case 79:
			return "O";
		case 80:
			return "P";
		case 81:
			return "Q";
		case 82:
			return "R";
		case 83:
			return "S";
		case 84:
			return "T";
		case 85:
			return "U";
		case 86:
			return "V";
		case 87:
			return "W";
		case 88:
			return "X";
		case 89:
			return "Y";
		case 90:
			return "Z";
		case 91:
			return "LEFT BRACKET";
		case 92:
			return "BACKSLASH";
		case 93:
			return "RIGHT BRACKET";
		case 96:
			return "GRAVE ACCENT";
		case 16:
			return "WORLD 1";
		case 25:
			return "ESCAPE";
		case 26:
			return "INSERT";
		case 28:
			return "CAPS LOCK";
		default:
			return nullptr;
	}
}
