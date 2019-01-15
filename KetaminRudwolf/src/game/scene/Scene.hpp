#pragma once
#include "../../render/Renderer.hpp"
#include "../../render/GUIRenderer.hpp"

class Scene {

protected:

	bool done;

public:
	Scene() : done(false) {}
	virtual ~Scene() {}

	virtual void onUpdate(std::chrono::milliseconds deltaTime) {} // In millis
	virtual void onRender(Renderer* renderer) {}
	virtual void onGUIRender(GUIRenderer* guiRenderer) {}
	virtual bool isDone() { return done; }
	virtual void onKey(int key, int scancode, int action, int modifiers) {}
	virtual void onMouseButton(int button, int action, int modifiers) {}
	virtual void onCursorPosition(double xPos, double yPos) {}
	virtual void onScroll(double xPos, double yPos) {}
};

