#pragma once

class EventHandler {

public:

	virtual void onKey(int key, int scancode, int action, int modifiers) = 0;
	virtual void onMouseButton(int button, int action, int modifiers) = 0;
	virtual void onCursorPosition(double xPos, double yPos) = 0;
	virtual void onScroll(double xPos, double yPos) = 0;
	virtual ~EventHandler() {};

};
