#include "GUIRenderer.hpp"
#include "../game/Game.hpp"

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION
#define NK_KEYSTATE_BASED_INPUT
#include <nuklear.h>
#include <nuklear_glfw_gl3.h>

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

struct nk_context *ctx;
struct nk_colorf bg;

GUIRenderer* GUIRenderer::instance = nullptr;

GUIRenderer::GUIRenderer() {
	bg.r = 0.10f;
	bg.g = 0.18f;
	bg.b = 0.24f;
	bg.a = 0.25f;
	ctx = nk_glfw3_init(Game::getInstance()->getWindow()->getGLFWWindow(), NK_GLFW3_DEFAULT);
	struct nk_font_atlas *atlas;
	nk_glfw3_font_stash_begin(&atlas);
	struct nk_font *clean = nk_font_atlas_add_from_file(atlas, "ProggyClean.ttf", 24, 0);
	nk_glfw3_font_stash_end();
	nk_style_load_all_cursors(ctx, atlas->cursors);
	nk_style_set_font(ctx, &clean->handle);
}

GUIRenderer::~GUIRenderer() {}

GUIRenderer* GUIRenderer::getInstance() {
	if (instance == nullptr) {
		instance = new GUIRenderer();
	}
	return instance;
}

void GUIRenderer::render() {
	nk_glfw3_render(NK_ANTI_ALIASING_OFF, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
}

void GUIRenderer::newFrame() {
	nk_glfw3_new_frame();
}

void GUIRenderer::begin(const char* title, int x, int y, int width, int height) {
	nk_begin(ctx, title, nk_rect(x, y, width, height), NK_WINDOW_NO_SCROLLBAR);
}

void GUIRenderer::beginBorderedWindow(const char* title, int x, int y, int width, int height) {
	nk_begin(ctx, title, nk_rect(x, y, width, height), NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_BACKGROUND | NK_WINDOW_BORDER);
}

void GUIRenderer::end() {
	nk_end(ctx);
}

void GUIRenderer::row(float height, int cols) {
	nk_layout_row_dynamic(ctx, height, cols);
}

bool GUIRenderer::button(const char *title) {
	return nk_button_label(ctx, title);
}

bool GUIRenderer::optionLabel(const char* title, bool active) {
	return nk_option_label(ctx, title, active);
}