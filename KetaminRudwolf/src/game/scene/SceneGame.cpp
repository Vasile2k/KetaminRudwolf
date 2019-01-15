#include "SceneGame.hpp"
#include "../Game.hpp"

SceneGame::SceneGame() {
	renderer = SDL_CreateRenderer(Game::getInstance()->getSDLWindow(), -1, 0);
	world = new World(renderer);
	player = new Player(renderer);
}

SceneGame::~SceneGame() {
	SDL_DestroyRenderer(renderer);
	delete player;
	delete world;
}

void SceneGame::onUpdate(std::chrono::milliseconds deltaTime) {
	//xPos += xScaleFactor * deltaTime.count();
	xPos += deltaTime.count();
	world->onUpdate(xPos);
	player->onUpdate(deltaTime);
}

void SceneGame::onRender(Renderer* r) {
	SDL_RenderClear(renderer);
	//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	//SDL_RenderDrawLine(renderer, 0, 0, 100, 100);
	world->onRender();
	player->onRender();
	SDL_RenderPresent(renderer);
}

void SceneGame::onGUIRender(GUIRenderer* guiRenderer) {
	/*if (isPaused) {
		guiRenderer->beginBorderedWindow("Escape Menu", Game::getInstance()->getWindow()->getWidth() / 2 - 75, 150, 150, 200);
		guiRenderer->row(15, 1);
		guiRenderer->row(70, 1);
		if (guiRenderer->button("Exit")) {
			done = true;
		}
		guiRenderer->row(15, 1);
		guiRenderer->row(70, 1);
		if (guiRenderer->button("Back")) {
			isPaused = false;
		}
		guiRenderer->end();
	}*/
}

void SceneGame::onKey(int key, int scancode, int action, int modifiers) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		//isPaused = true;
		done = true;
	}
	if (key == GLFW_KEY_SPACE) {
		if (action == GLFW_PRESS) {
			player->jump();
		}
	}
}

bool SceneGame::requireClearing() {
	return false;
}
