#pragma once

class GUIRenderer {

private:

	static GUIRenderer* instance;
	GUIRenderer();
	~GUIRenderer();

public:

	static GUIRenderer* getInstance();
	void newFrame();
	void render();
	void begin(const char* title, int x, int y, int width, int height);
	void beginBorderedWindow(const char* title, int x, int y, int width, int height);
	void end();
	void row(float height, int cols);
	bool button(const char *title);
	bool optionLabel(const char* title, bool active);
};

