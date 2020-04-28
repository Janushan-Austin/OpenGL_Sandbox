#include "CallBackFunctions.h"

void framebuffer_size_callback(GLFWwindow* window, int newHeight, int newWidth) {
	glViewport(0, 0, newWidth, newHeight);
}

