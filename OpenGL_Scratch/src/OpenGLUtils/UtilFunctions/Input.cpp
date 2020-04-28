#include "OpenGLUtils/OpenGLUtils.h"

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void processCameraInput(GLFWwindow * window, glm::vec3& cameraPos, glm::vec3& cameraFront, glm::vec3& cameraUp, float cameraSpeed, float deltaTime) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cameraPos += cameraSpeed * cameraFront * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraPos -= cameraSpeed * cameraFront * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime;
	}
}