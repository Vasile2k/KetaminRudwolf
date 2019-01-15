#include "SceneGame.hpp"
#include "../Game.hpp"

SceneGame::SceneGame() {
	renderer = SDL_CreateRenderer(Game::getInstance()->getSDLWindow(), -1, 0);
	world = new World(renderer);
	player = new Player(renderer);
	enemy = new Enemy(renderer);
}

SceneGame::~SceneGame() {
	SDL_DestroyRenderer(renderer);
	delete enemy;
	delete player;
	delete world;
}

void SceneGame::onUpdate(std::chrono::milliseconds deltaTime) {
	//xPos += xScaleFactor * deltaTime.count();
	if (!player->died()) {
		xPos += deltaTime.count();
		world->onUpdate(xPos);
		enemy->onUpdate(deltaTime);
		if (player->checkCollision(enemy)) {
			player->die();
		}
	}
	player->onUpdate(deltaTime);
}

void SceneGame::onRender(Renderer* r) {
	SDL_RenderClear(renderer);
	world->onRender();
	if (!player->died()) {
		enemy->onRender();
	}
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
	if (key == Game::getInstance()->getJumpKey()) {
		if (action == GLFW_PRESS) {
			player->jump();
		}
	} else if (key == Game::getInstance()->getCrouchKey()) {
		if (action == GLFW_PRESS) {
			player->crouch();
		}
	}
}

bool SceneGame::requireClearing() {
	return false;
}
