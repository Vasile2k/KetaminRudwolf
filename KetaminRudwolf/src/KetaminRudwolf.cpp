#include "game/Game.hpp"

int main() {

	Game *game = new Game();
	int status = game->exec();
	delete game;

	return status;
}