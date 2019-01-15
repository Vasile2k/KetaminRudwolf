#pragma once

class Enemy {

private:
	int spriteWidth = 67;
	int spriteHeight = 32;
	int spriteX = 0;
	int spriteY = 0;
	float xPos = 5000.0F;
	float yPos = 500.0F;
	SDL_Renderer* renderer;
	SDL_Texture* texture;

	int millisSinceLastUpdate = 0;

public:
	Enemy(SDL_Renderer* r);
	~Enemy();
	void onRender();
	void onUpdate(std::chrono::milliseconds deltaTime);
	// Enemy is friend with player :D
	friend class Player;
};

