#pragma once
#include "Scene.hpp"

class SceneOptions : public Scene {

public:
	SceneOptions();
	~SceneOptions();
	void onUpdate(std::chrono::milliseconds deltaTime) override;
	void onRender(Renderer* renderer) override;
	void onGUIRender(GUIRenderer* guiRenderer) override;
	void onMouseButton(int button, int action, int modifiers) override;
};
