#include "Debug.hpp"
#include "game/Game.hpp"

entry_point{

	Game::create();
	int status = Game::getInstance()->exec();
	Game::destroy();
	return status;
}
