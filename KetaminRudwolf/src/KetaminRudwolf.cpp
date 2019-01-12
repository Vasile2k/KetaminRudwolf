#include <iostream>
#include <windows.h>
#define GLEW_STATIC
#include <GLEW\glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW\glfw3.h>

int main() {

	glewInit();
	glfwInit();

	std::cout << "Rudwolf, the dog on da' Key!" << std::endl;
	return 0;
}