#pragma once
#include "Scene.hpp"

class SceneMenu : public Scene {

private:
	Scene*& currentScene;

public:
	SceneMenu(Scene*& currentScene);
	~SceneMenu();
	void onUpdate(std::chrono::milliseconds deltaTime) override;
	void onRender(Renderer* renderer) override;
	void onGUIRender(GUIRenderer* guiRenderer) override;
	void onMouseButton(int button, int action, int modifiers) override;
};
