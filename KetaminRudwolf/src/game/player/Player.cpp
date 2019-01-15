#include "Player.hpp"

#include <SDL_image.h>

Player::Player(SDL_Renderer* r) : renderer(r) {
	texture = IMG_LoadTexture(renderer, "res/tex/Player/santa.png");
}

Player::~Player() {
	SDL_DestroyTexture(texture);
}

void Player::onRender() {
	SDL_Rect texRect = { spriteX*spriteWidth, spriteY*spriteHeight, spriteWidth - 1, spriteHeight - 1 };
	SDL_Rect windowRectBg0 = { int(xPos), int(yPos), spriteWidth * 4, spriteHeight * 4 };
	SDL_RenderCopy(renderer, texture, &texRect, &windowRectBg0);
}

void Player::onUpdate(std::chrono::milliseconds deltaTime) {
	millisSinceLastUpdate += deltaTime.count();
	if (millisSinceLastUpdate > 50) {
		if (isJumping) {
			spriteY = 5;
		} else {
			spriteY = 1;
		}
		spriteX++;
		spriteX %= isJumping ? 9 : 8;
		millisSinceLastUpdate -= 50;
	}

	if (yPos >= yTarget) {
		yPos = yTarget;
		ySpeed = 0.0F;
		isJumping = false;
	} else {
		yPos += ySpeed;
		ySpeed += 0.001F * deltaTime.count();
	}

}

void Player::jump() {
	if (!isJumping) {
		isJumping = true;
		ySpeed = -0.5f;
		yPos += ySpeed;
	}
}
