#pragma once
#include "Scene.hpp"
#include "../player/World.hpp"
#include "../player/Player.hpp"
#include "../player/Enemy.hpp"
#include <SDL_ttf.h>

class SceneGame : public Scene {

private:

	bool isPaused = false;
	SDL_Renderer* renderer = nullptr;
	TTF_Font* font;
	World* world;
	Player* player;
	Enemy* enemy;
	int xScaleFactor = 0;
	int xPos = 0;

public:
	SceneGame();
	~SceneGame();
	void onUpdate(std::chrono::milliseconds deltaTime) override;
	void onRender(Renderer* renderer) override;
	void onGUIRender(GUIRenderer* guiRenderer) override;
	void onKey(int key, int scancode, int action, int modifiers) override;
	bool requireClearing();
};

