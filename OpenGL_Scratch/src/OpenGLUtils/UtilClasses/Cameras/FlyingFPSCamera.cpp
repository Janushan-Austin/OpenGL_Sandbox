#include "FlyingFPSCamera.h"



FlyingFPSCamera::FlyingFPSCamera(glm::vec3 pos, float fov, float y, float p, float r) :Camera(pos, fov, y, p, r)
{
	UpdateCameraVectors();
}


FlyingFPSCamera::~FlyingFPSCamera()
{
}

void FlyingFPSCamera::ProcessMouseMovement(float xOffset, float yOffset)
{
	xOffset *= MouseSensitivity, yOffset *= MouseSensitivity;

	yaw += xOffset;
	pitch -= yOffset;

	if (pitch >89.0f) {
		pitch = 89.0f;
	}
	else if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	UpdateCameraVectors();
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

void FlyingFPSCamera::UpdateCameraVectors()
{
	glm::vec3 front;
	float yRad = glm::radians(yaw), pRad = glm::radians(pitch);
	front.x = cos(yRad) * cos(pRad);
	front.y = sin(pRad);
	front.z = sin(yRad) * cos(pRad);

	cameraFront = glm::normalize(front);
	cameraRight = glm::cross(cameraFront, cameraRotationPlaneUp);
	cameraUp = glm::cross(cameraRight, cameraFront);
}
