#include "MouseGLCallbackWrapper.h"

Camera* MouseGLCallbackWrapper::camera = NULL;
int MouseGLCallbackWrapper::lastX = 0;
int MouseGLCallbackWrapper::lastY = 0;
bool MouseGLCallbackWrapper::firstMouseMove = true;

void MouseGLCallbackWrapper::mouse_Movement_Callback(GLFWwindow* window, double xPos, double yPos) {
	if (camera != NULL) {
		if (firstMouseMove) {
			lastX = xPos;
			lastY = yPos;
			firstMouseMove = false;
		}

		camera->ProcessMouseMovement((float)(xPos - lastX), (float)(yPos - lastY));

		lastX = xPos;
		lastY = yPos;
	}
}

void MouseGLCallbackWrapper::mouse_Scroll_Callback(GLFWwindow* window, double xOffset, double yOffset) {
	if (camera != NULL) {
		camera->ProcessMouseScroll((float)yOffset);
	}
}