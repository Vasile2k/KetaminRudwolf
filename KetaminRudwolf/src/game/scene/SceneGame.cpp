#include "SceneGame.hpp"
#include "../Game.hpp"

SceneGame::SceneGame() {

}

SceneGame::~SceneGame() {

}

void SceneGame::onUpdate(std::chrono::milliseconds deltaTime) {

}

void SceneGame::onRender(Renderer* renderer) {
	renderer->clear();
	renderer->clearColor(0.0F, 0.5F, 1.0F, 1.0F);
}

void SceneGame::onGUIRender(GUIRenderer* guiRenderer) {
	if (isPaused) {
		guiRenderer->beginBorderedWindow("Escape Menu", Game::getInstance()->getWindow()->getWidth() / 2 - 75, 150, 150, 200);
		guiRenderer->row(15, 1);
		guiRenderer->row(70, 1);
		if (guiRenderer->button("Exit")) {
			done = true;
		}
		guiRenderer->row(15, 1);
		guiRenderer->row(70, 1);
		if (guiRenderer->button("Back")) {
			isPaused = false;
		}
		guiRenderer->end();
	}
}

void SceneGame::onKey(int key, int scancode, int action, int modifiers) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		isPaused = true;
	}
}
