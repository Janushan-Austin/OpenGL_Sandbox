#include "FlyingFPSCamera.h"



FlyingFPSCamera::FlyingFPSCamera(glm::vec3 pos, float fov, float y, float p, float r) :Camera(pos, fov, y, p, r)
{
}


FlyingFPSCamera::~FlyingFPSCamera()
{
}

void FlyingFPSCamera::ProcessMouseMovement(float xOffset, float yOffset)
{
	xOffset *= MouseSensitivity, yOffset *= MouseSensitivity;

	ApplyYaw(xOffset);
	ApplyPitch(yOffset);
}

void FlyingFPSCamera::ProcessKeyboardInput(MovementDirection direction, float deltaTime)
{

	if (direction == MovementDirection::FORWARD) {
		cameraPos += cameraFront * CameraSpeed * deltaTime;
	}
	else if (direction == MovementDirection::BACKWARD) {
		cameraPos -= cameraFront * CameraSpeed * deltaTime;
	}
	else if (direction == MovementDirection::LEFT) {
		cameraPos -= cameraRight * CameraSpeed * deltaTime;
	}
	else if (direction == MovementDirection::RIGHT) {
		cameraPos += cameraRight * CameraSpeed * deltaTime;
	}
	else if (direction == MovementDirection::UP) {
		cameraPos += cameraUp * CameraSpeed * deltaTime;
	}
	else if (direction == MovementDirection::DOWN) {
		cameraPos -= cameraUp * CameraSpeed * deltaTime;
	}
}

void FlyingFPSCamera::ProcessMouseScroll(float yOffset)
{
	if (fov >= 1.0f && fov <= 120.0f) {
		fov -= yOffset;
	}

	if (fov < 1.0f) {
		fov = 1.0f;
	}
	else if (fov > 120.0f) {
		fov = 120.0f;
	}
}

void FlyingFPSCamera::ApplyPitch(float pitchOffset)
{
	pitch -= pitchOffset;
	cameraFront = glm::normalize((cameraFront * cosf(glm::radians(-pitchOffset))) + (glm::vec3(0.0f, 1.0f, 0.0f) * sinf(glm::radians(-pitchOffset))));

	cameraUp = glm::cross(cameraRight, cameraFront);
}
