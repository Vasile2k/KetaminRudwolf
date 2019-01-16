#include "SceneGame.hpp"
#include "../Game.hpp"

SceneGame::SceneGame() {
	if (TTF_Init() == -1) {
		throw new std::runtime_error(TTF_GetError());

	}
	renderer = SDL_CreateRenderer(Game::getInstance()->getSDLWindow(), -1, 0);
	font = TTF_OpenFont("res/font/ProggyClean.ttf", 69);
	const char* s = TTF_GetError();
	world = new World(renderer);
	player = new Player(renderer);
	enemy = new Enemy(renderer);
}

SceneGame::~SceneGame() {
	TTF_CloseFont(font);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
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

	std::string score = "Score: ";
	score += std::to_string(player->getScore());

	SDL_Surface* surface;
	surface = TTF_RenderText_Solid(font, score.c_str(), { 0, 0, 0, 255 });
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect textRect = { 0, 0, surface->w, surface->h };
	SDL_Rect windowRect = { 100, 100, surface->w, surface->h };
	SDL_RenderCopy(renderer, texture, &textRect, &windowRect);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);

	if (player->died()) {
		surface = TTF_RenderText_Solid(font, "Press ESCAPE to continue.", { 0, 0, 0, 255 });
		texture = SDL_CreateTextureFromSurface(renderer, surface);

		textRect = { 0, 0, surface->w, surface->h };
		windowRect = { 100, 200, surface->w, surface->h };
		SDL_RenderCopy(renderer, texture, &textRect, &windowRect);

		SDL_DestroyTexture(texture);
		SDL_FreeSurface(surface);
	}

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
