#include "SceneOptions.hpp"
#include "../Game.hpp"

SceneOptions::SceneOptions() {

}

SceneOptions::~SceneOptions() {

}

void SceneOptions::onUpdate(std::chrono::milliseconds deltaTime) {

}

void SceneOptions::onRender(Renderer* renderer) {
	renderer->clear();
	renderer->clearColor(0.176470588F, 0.176470588F, 0.176470588F, 1.0F);
}

void SceneOptions::onGUIRender(GUIRenderer* guiRenderer) {
	guiRenderer->beginBorderedWindow("Options", (float)Game::getInstance()->getWindow()->getWidth() / 2.0F - 175.0F, 200.0F, 350.0F, 300.0F);
	guiRenderer->row(15, 1);
	guiRenderer->row(70, 1);
	std::string jumpKey = setJumpKey ? "Press any key" : "Jump key : ";
	if (!setJumpKey) {
		jumpKey += getKeyName(Game::getInstance()->getJumpKey());
	}
	if (guiRenderer->button(jumpKey.c_str())) {
		setJumpKey = true;
		setCrouchKey = false;
	}
	guiRenderer->row(15, 1);
	guiRenderer->row(70, 1);
	std::string crouchKey = setCrouchKey ? "Press any key" : "Crouch key : ";
	if (!setCrouchKey) {
		crouchKey += getKeyName(Game::getInstance()->getCrouchKey());
	}
	if (guiRenderer->button(crouchKey.c_str())) {
		setCrouchKey = true;
		setJumpKey = false;
	}
	guiRenderer->row(15, 1);
	guiRenderer->row(70, 1);
	if (guiRenderer->button("Back")) {
		done = true;
	}
	guiRenderer->end();
}

void SceneOptions::onMouseButton(int button, int action, int modifiers) {

}

void SceneOptions::onKey(int key, int scancode, int action, int modifiers) {
	if (setJumpKey) {
		if (isValidKey(key)) {
			if (key != Game::getInstance()->getCrouchKey()) {
				Game::getInstance()->setJumpKey(key);
				setJumpKey = false;
			}
		}
	} if (setCrouchKey) {
		if (isValidKey(key)) {
			if (key != Game::getInstance()->getJumpKey()) {
				Game::getInstance()->setCrouchKey(key);
				setCrouchKey = false;
			}
		}
	}
}
