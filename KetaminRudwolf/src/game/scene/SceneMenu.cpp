#include "SceneMenu.hpp"
#include "SceneOptions.hpp"
#include "SceneGame.hpp"
#include "../Game.hpp"

SceneMenu::SceneMenu(Scene*& currentScene) : currentScene(currentScene) {

}

SceneMenu::~SceneMenu() {

}

void SceneMenu::onUpdate(std::chrono::milliseconds deltaTime) {

}

void SceneMenu::onRender(Renderer* renderer) {
	renderer->clear();
	renderer->clearColor(0.176470588F, 0.176470588F, 0.176470588F, 1.0F);
}

void SceneMenu::onGUIRender(GUIRenderer* guiRenderer) {
	guiRenderer->begin("Game", Game::getInstance()->getWindow()->getWidth() / 2 - 100, 100, 200, 300);
	guiRenderer->row(15, 1);
	guiRenderer->row(70, 1);
	if (guiRenderer->button("Play")) {
		currentScene = new SceneGame();
	}
	guiRenderer->row(15, 1);
	guiRenderer->row(70, 1);
	if (guiRenderer->button("Options")) {
		currentScene = new SceneOptions();
	}
	guiRenderer->row(15, 1);
	guiRenderer->row(70, 1);
	if (guiRenderer->button("Exit")) {
		done = true;
	}
	guiRenderer->end();
}


void SceneMenu::onMouseButton(int button, int action, int modifiers) {

}
