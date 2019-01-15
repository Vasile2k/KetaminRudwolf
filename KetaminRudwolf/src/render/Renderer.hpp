#pragma once

class Renderer {

private:

	static Renderer* instance;
	Renderer();
	~Renderer();

public:

	static Renderer* getInstance();
	void clear();
	void clearColor(float r, float g, float b, float alpha);
	void viewport(int x, int y, int width, int height);
};

