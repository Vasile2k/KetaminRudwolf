#include "Player.hpp"

#include <SDL_image.h>

Player::Player(SDL_Renderer* r) : renderer(r) {
	texture = IMG_LoadTexture(renderer, "res/tex/Player/santa.png");
	explosion = IMG_LoadTexture(renderer, "res/tex/Explosion/exp2_0.png");
}

Player::~Player() {
	SDL_DestroyTexture(explosion);
	SDL_DestroyTexture(texture);
}

void Player::onRender() {
	SDL_Rect texRect = { spriteX*spriteWidth, spriteY*spriteHeight, spriteWidth - 1, spriteHeight - 1 };
	SDL_Rect windowRect = { int(xPos), int(yPos), spriteWidth * 4, spriteHeight * 4 };
	SDL_RenderCopy(renderer, texture, &texRect, &windowRect);
	if (isDead) {
		if (explosionState < 16) {
			SDL_Rect expRect = { (explosionState % 4) * 64, (explosionState / 4) * 64, 64, 64 };
			SDL_Rect windowRectExp = { int(xPos), int(yPos), 356, 356 };
			SDL_RenderCopy(renderer, explosion, &expRect, &windowRectExp);
		}
	}
}

void Player::onUpdate(std::chrono::milliseconds deltaTime) {
	millisSinceLastUpdate += deltaTime.count();
	speed += 0.0001F;
	if (!isDead) {
		score += 0.001F * deltaTime.count() * speed;
	}
	if (millisSinceLastUpdate > 50) {
		spriteX++;
		if (isDead) {
			spriteY = 10;
			spriteX = min(spriteX, 6);
			++explosionState;
			explosionState = min(explosionState, 16);
		} else if (isJumping) {
			spriteY = 5;
			spriteX %= 9;
		} else if (isCrouching) {
			spriteY = 6;
			if (spriteX == 8) {
				spriteX = 0;
				isCrouching = false;
			}
		} else {
			spriteY = 1;
			spriteX %= 8;
		}
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
	if (!isDead) {
		if (!isJumping) {
			isJumping = true;
			ySpeed = -0.5f;
			yPos += ySpeed;
		}
		isCrouching = false;
	}
}

void Player::crouch() {
	if (!isDead) {
		isCrouching = true;
		spriteY = 6;
		spriteX = 0;
	}
}

void Player::die() {
	isDead = true;
	spriteY = 10;
}

bool Player::died() {
	return isDead;
}

bool Player::checkCollision(Enemy* enemy) {
	if (!isJumping) {
		return fabs(enemy->xPos - this->xPos) < 150.0F;
	}
	return false;
}

int Player::getScore() {
	return (int)score;
}
