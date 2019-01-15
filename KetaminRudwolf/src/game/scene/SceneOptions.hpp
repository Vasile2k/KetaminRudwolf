#pragma once
#include "Scene.hpp"

class SceneOptions : public Scene {

private:

	bool setJumpKey = false;
	bool setCrouchKey = false;

public:
	SceneOptions();
	~SceneOptions();
	void onUpdate(std::chrono::milliseconds deltaTime) override;
	void onRender(Renderer* renderer) override;
	void onGUIRender(GUIRenderer* guiRenderer) override;
	void onMouseButton(int button, int action, int modifiers) override;
	void onKey(int key, int scancode, int action, int modifiers) override;
};
