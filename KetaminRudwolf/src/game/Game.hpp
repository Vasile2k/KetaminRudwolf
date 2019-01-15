#pragma once
#include "../window/Window.hpp"
#include "scene/Scene.hpp"
#include "scene/SceneMenu.hpp"

class Game {

private:

	static Game* instance;
	Window* m_Window;
	SceneMenu* m_MenuScene;
	Scene* m_CurrentScene;

	Game();
	~Game();

public:

	static Game* getInstance();
	static void create();
	static void destroy();
	int exec();
	Window* getWindow();

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
