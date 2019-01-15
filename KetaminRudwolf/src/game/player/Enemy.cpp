#include "Enemy.hpp"

#include <SDL_image.h>

Enemy::Enemy(SDL_Renderer* r) : renderer(r) {
	texture = IMG_LoadTexture(renderer, "res/tex/Enemy/hell-hound-run.png");
}

Enemy::~Enemy() {
	SDL_DestroyTexture(texture);
}

void Enemy::onRender() {
	SDL_Rect texRect = { spriteX*spriteWidth, spriteY*spriteHeight, spriteWidth - 1, spriteHeight - 1 };
	SDL_Rect windowRectBg0 = { int(xPos), int(yPos), spriteWidth * 4, spriteHeight * 4 };
	SDL_RenderCopy(renderer, texture, &texRect, &windowRectBg0);
}

void Enemy::onUpdate(std::chrono::milliseconds deltaTime) {
	millisSinceLastUpdate += deltaTime.count();
	xPos -= deltaTime.count();
	if (xPos < -500) {
		xPos = 1500 + rand() % 2000;
	}
	if (millisSinceLastUpdate > 100) {
		spriteX++;
		spriteX %= 5;
		millisSinceLastUpdate -= 100;
	}
}
