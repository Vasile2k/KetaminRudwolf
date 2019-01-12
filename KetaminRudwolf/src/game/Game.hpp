#pragma once

#include "../window/Window.hpp"

#define GLEW_STATIC
#include <GLEW/glew.h>

class Game {

private:

	Window *m_Window;

public:

	Game();
	int exec();
	~Game();

};
