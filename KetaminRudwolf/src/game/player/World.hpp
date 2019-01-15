#pragma once

class World {

private:

	SDL_Texture* bg0 = nullptr;
	SDL_Texture* bg1 = nullptr;
	SDL_Texture* fg = nullptr;
	SDL_Renderer* renderer = nullptr;
	int xPos = 0;

	void renderBackgroundLayer(int x, SDL_Texture* t, SDL_Renderer* renderer);

public:
	World(SDL_Renderer* renderer);
	~World();
	void onRender();
	void onUpdate(int xPos);
};
