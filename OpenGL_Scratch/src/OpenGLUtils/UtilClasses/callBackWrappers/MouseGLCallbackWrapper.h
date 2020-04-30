#pragma once
#include "OpenGLUtils/OpenGLUtils.h"
#include "OpenGLUtils/UtilClasses/Cameras/Camera.h"

class MouseGLCallbackWrapper {
public:
	static int lastX, lastY;
	static bool firstMouseMove;
	static Camera* camera;

	static void mouse_Movement_Callback(GLFWwindow* window, double xPos, double yPos);
	static void mouse_Scroll_Callback(GLFWwindow* window, double xOffset, double yOffset);
};
//Camera* MouseGLCallbackWrapper::camera = NULL;
//int MouseGLCallbackWrapper::lastX = 0;
//int MouseGLCallbackWrapper::lastY = 0;
//bool MouseGLCallbackWrapper::firstMouseMove = true;