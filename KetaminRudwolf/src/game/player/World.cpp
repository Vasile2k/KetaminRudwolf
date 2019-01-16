#include "World.hpp"
#include <SDL_image.h>

World::World(SDL_Renderer* r) : renderer(r) {
	bg0 = IMG_LoadTexture(renderer, "res/tex/World/bg0.png");
	bg1 = IMG_LoadTexture(renderer, "res/tex/World/bg1.png");
	fg = IMG_LoadTexture(renderer, "res/tex/World/fg.png");
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
}

World::~World() {
	SDL_DestroyTexture(bg0);
	SDL_DestroyTexture(bg1);
	SDL_DestroyTexture(fg);
}

void World::onRender() {
	renderBackgroundLayer(int(speed*(xPos / 8)), bg0, renderer);
	renderBackgroundLayer(int(speed*(xPos / 4)), bg1, renderer);
	renderBackgroundLayer(int(speed*(xPos / 2)), fg, renderer);
}

void World::renderBackgroundLayer(int x, SDL_Texture* t, SDL_Renderer* renderer) {
	int width = 1280;
	int height = 720;
	int xPosition = (x % width + width) % width;
	SDL_Rect texRect = { 0, 0, 384, 224 };
	SDL_Rect windowRectBg0 = { -xPosition, 0, width, height };
	SDL_RenderCopy(renderer, t, &texRect, &windowRectBg0);
	windowRectBg0 = { -xPosition + width, 0, width, height };
	SDL_RenderCopy(renderer, t, &texRect, &windowRectBg0);
}

void World::onUpdate(int xPos) {
	this->xPos = xPos;
	speed += 0.0001F;
}
