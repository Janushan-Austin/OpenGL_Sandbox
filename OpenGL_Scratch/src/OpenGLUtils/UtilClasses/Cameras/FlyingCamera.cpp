#include "FlyingCamera.h"



FlyingCamera::FlyingCamera(glm::vec3 pos, float fov, float y, float p, float r) :Camera(pos, fov, y, p, r)
{
}


FlyingCamera::~FlyingCamera()
{
}

void FlyingCamera::ProcessMouseMovement(float xOffset, float yOffset)
{
	xOffset *= MouseSensitivity, yOffset *= MouseSensitivity;

	ApplyYaw(xOffset);
	ApplyPitch(yOffset);
}

void FlyingCamera::ProcessKeyboardInput(MovementDirection direction, float deltaTime)
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
	else if (direction == MovementDirection::ROLL_LEFT) {
		ApplyRoll(CameraSpeed * deltaTime * 100 );
	}
	else if (direction == MovementDirection::ROLL_RIGHT) {
		ApplyRoll(-CameraSpeed * deltaTime * 100);
	}
}

void FlyingCamera::ProcessMouseScroll(float yOffset)
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