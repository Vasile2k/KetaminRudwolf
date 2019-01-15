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
	std::string jumpKey = "Jump key : ";
	jumpKey += getKeyName(Game::getInstance()->getJumpKey());
	if (guiRenderer->button(jumpKey.c_str())) {

	}
	guiRenderer->row(15, 1);
	guiRenderer->row(70, 1);
	std::string crouchKey = "Jump key : ";
	crouchKey += getKeyName(Game::getInstance()->getCrouchKey());
	if (guiRenderer->button(crouchKey.c_str())) {

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
