#pragma once
#include "Enemy.hpp"

class Player {

private:

	int width = 1280;
	int height = 720;
	int spriteWidth = 96;
	int spriteHeight = 96;
	int spriteX = 0;
	int spriteY = 1;

	int explosionState = 0;

	float xPos = 250.0F;
	float yTarget = 370.0F;
	float yPos = yTarget;
	float ySpeed = 0.0F;
	bool isJumping = false;
	bool isCrouching = false;
	bool isDead = false;

	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Texture* explosion;

	int millisSinceLastUpdate = 0;

public:
	Player(SDL_Renderer* r);
	~Player();
	void onRender();
	void onUpdate(std::chrono::milliseconds deltaTime);
	void jump();
	void crouch();
	void die();
	bool died();
	bool checkCollision(Enemy* enemy);
};
