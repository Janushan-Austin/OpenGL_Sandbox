#include "CallBackFunctions.h"

void framebuffer_size_callback(GLFWwindow* window, int newHeight, int newWidth) {
	glViewport(0, 0, newWidth, newHeight);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}