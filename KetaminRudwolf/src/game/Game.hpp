#pragma once
#include "../window/Window.hpp"
#include "scene/Scene.hpp"
#include "scene/SceneMenu.hpp"

class Game {

private:

	static Game* instance;
	Window* m_Window;
	SDL_Window* m_SDLWindow;
	SceneMenu* m_MenuScene;
	Scene* m_CurrentScene;

	int m_JumpKey = GLFW_KEY_SPACE;
	int m_CrouchKey = GLFW_KEY_C;

	Game();
	~Game();

public:

	static Game* getInstance();
	static void create();
	static void destroy();
	int exec();
	int getJumpKey();
	int getCrouchKey();
	void setJumpKey(int key);
	void setCrouchKey(int key);
	Window* getWindow();
	SDL_Window* getSDLWindow();

	friend class GameHandler;
	class GameHandler : public EventHandler {
	public:
		GameHandler();
		~GameHandler();
		void onKey(int key, int scancode, int action, int modifiers);
		void onMouseButton(int button, int action, int modifiers);
		void onCursorPosition(double xPos, double yPos);
		void onScroll(double xPos, double yPos);
	};

};

std::chrono::milliseconds getCurrentTime();
const char* getKeyName(int key);
bool isValidKey(int key);