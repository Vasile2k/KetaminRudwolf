#pragma once

#ifdef _DEBUG
#define entry_point int main()
#else
#define entry_point int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
#endif

#ifdef _DEBUG

#include <sstream>
#include <csignal>

#if defined(_MSC_VER)
#define BREAK __debugbreak();
#else
#define BREAK raise(SIGINT)
#endif

#define ASSERT(x)\
	if (!(x))\
		BREAK;
#define GLCall(x)\
	GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError() {
	while (glGetError() != GL_NO_ERROR) {
		;
	}
}

bool GLLogCall(const char *function, const char *file, int line) {

	static const std::string GLErrors[] = {
		"GL_INVADIL_ENUM", "GL_INVALID_VALUE", "GL_INVALID_OPERATION", "GL_STACK_OVERFLOW", "GL_STACK_UNDERFLOW",
		"GL_OUT_OF_MEMORY", "GL_INVALID_FRAMEBUFFER_OPERATION", "GL_CONTEXT_LOST", "GL_TABLE_TOO_LARGE"
	};

	GLenum error;
	while ((error = glGetError())) {
		std::stringstream ss;
		ss << std::hex << error;
		fprintf(stderr, "[OpenGL Error] (0x%s : %s): %s %s: %d\n", ss.str().c_str(), GLErrors[error - 1280].c_str(), function, file, line);
		return false;
	}
	return true;
}

#else

#endif
