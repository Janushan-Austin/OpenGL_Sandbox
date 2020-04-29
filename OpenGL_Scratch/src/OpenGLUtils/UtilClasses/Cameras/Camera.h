#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	Camera(glm::vec3 pos = glm::vec3(0.0f), float fov = 90.0f, float y = 0.0f, float p = 0.0f, float r = 0.0f);
	virtual ~Camera();

	virtual glm::mat4 GenerateViewMatrix();


	inline const glm::vec3& Position() { return cameraPos; }
	inline const glm::vec3& Front() { return cameraFront; }
	inline const glm::vec3& Right() { return cameraRight; }
	inline const glm::vec3& Up() { return cameraUp; }
	inline const glm::vec3& RotationPlaneUp() { return cameraRotationPlaneUp; }
	inline const float& FOV() { return fov; }

	virtual void ProcessMouseMovement(float xOffset, float yOffset) =0;
	virtual void ProcessKeyboardInput(MovementDirection direction, float deltaTime) = 0;
	virtual void ProcessMouseScroll(float yOffset) =0;
protected:

	virtual void UpdateCameraVectors() = 0;

	glm::vec3 cameraPos, cameraFront, cameraRight, cameraUp;
	glm::vec3 cameraRotationPlaneUp;

	float yaw, pitch, roll;
	int deltaRoll;

	float fov;
};

