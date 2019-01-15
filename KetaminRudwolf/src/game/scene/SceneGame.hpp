#pragma once
#include "Scene.hpp"

class SceneGame : public Scene {

private:

	bool isPaused = false;

public:
	SceneGame();
	~SceneGame();
	void onUpdate(std::chrono::milliseconds deltaTime) override;
	void onRender(Renderer* renderer) override;
	void onGUIRender(GUIRenderer* guiRenderer) override;
	void onKey(int key, int scancode, int action, int modifiers) override;
};

