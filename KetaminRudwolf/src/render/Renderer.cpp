#include "Renderer.hpp"

Renderer* Renderer::instance = nullptr;

Renderer::Renderer() {}

Renderer::~Renderer() {}

Renderer* Renderer::getInstance() {
	if (instance == nullptr) {
		instance = new Renderer();
	}
	return instance;
}

void Renderer::clear() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void Renderer::clearColor(float r, float g, float b, float alpha) {
	glClearColor(r, g, b, alpha);
}

void Renderer::viewport(int x, int y, int width, int height) {
	glViewport(x, y, width, height);
}
