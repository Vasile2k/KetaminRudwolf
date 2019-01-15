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
	guiRenderer->beginBorderedWindow("Options", Game::getInstance()->getWindow()->getWidth() / 2 - 175, 150, 350, 200);
	guiRenderer->row(15, 1);
	guiRenderer->row(70, 2);

	enum { WINDOWED, FULLSCREEN };
	static int state = Game::getInstance()->getWindow()->getFullscreen();

	if (guiRenderer->optionLabel("Windowed", state == WINDOWED)) {
		Game::getInstance()->getWindow()->setFullscreen(false);
		Game::getInstance()->getWindow()->setResolution(1280, 720);
		state = WINDOWED;
	}
	if (guiRenderer->optionLabel("Fullscreen", state == FULLSCREEN)) {
		Game::getInstance()->getWindow()->setFullscreen(true);
		state = FULLSCREEN;
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
