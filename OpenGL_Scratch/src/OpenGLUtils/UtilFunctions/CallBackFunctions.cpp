#include "CallBackFunctions.h"

void framebuffer_size_callback(GLFWwindow* window, int newWidth, int newHeight) {
	glViewport(0, 0, newWidth, newHeight);
}

