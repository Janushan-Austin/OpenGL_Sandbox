#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

enum class MovementDirection {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	ROLL_LEFT,
	ROLL_RIGHT,
};

const float MouseSensitivity = 0.1f;
const float CameraSpeed = 2.5f;

class Camera
{
public:
	Camera(glm::vec3 pos = glm::vec3(0.0f), unsigned int width = 800, unsigned int height =600, float fov = 90.0f, float y = 0.0f, float p = 0.0f, float r = 0.0f);
	virtual ~Camera();

	virtual glm::mat4 GenerateViewMatrix();


	inline const glm::vec3& Position() { return cameraPos; }
	inline const glm::vec3& Front() { return cameraFront; }
	inline const glm::vec3& Right() { return cameraRight; }
	inline const glm::vec3& Up() { return cameraUp; }
	inline const float& FOV() { return fov; }
	inline const unsigned int& Height() { return height; }
	inline const unsigned int& Width() { return width; }
	inline void SetDimmensions(unsigned int width_, unsigned int height_) { width = width_; height = height_; }

	virtual void ProcessMouseMovement(float xOffset, float yOffset) =0;
	virtual void ProcessKeyboardInput(MovementDirection direction, float deltaTime) = 0;
	virtual void ProcessMouseScroll(float yOffset) =0;
	virtual void WindowResizeEvent(GLFWwindow* window, int width, int height);
protected:
	glm::vec3 cameraPos, cameraFront, cameraRight, cameraUp;

	unsigned int width, height;

	float yaw, pitch, roll;

	float fov;
};

