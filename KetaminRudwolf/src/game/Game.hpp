#pragma once
#include "../window/Window.hpp"

class Game {

private:

	static Game* instance;
	Window *m_Window;

	Game();
	~Game();

public:

	static Game* getInstance();
	static void create();
	static void destroy();
	int exec();
	Window* getWindow();

};
