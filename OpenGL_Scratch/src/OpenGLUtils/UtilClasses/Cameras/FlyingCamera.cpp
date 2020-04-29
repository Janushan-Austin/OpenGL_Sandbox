#include "FlyingCamera.h"



FlyingCamera::FlyingCamera(glm::vec3 pos, float fov, float y, float p, float r) :Camera(pos, fov, y, p, r), greaterThanNinety(false)
{
	UpdateCameraVectors();
}


FlyingCamera::~FlyingCamera()
{
}

void FlyingCamera::ProcessMouseMovement(float xOffset, float yOffset)
{
	xOffset *= MouseSensitivity, yOffset *= MouseSensitivity;
	float rRad = glm::radians(roll);

	if (!greaterThanNinety) {
		yaw += xOffset *cos(rRad) - yOffset * sin(rRad);
	}
	else {
		yaw -= xOffset *cos(rRad) - yOffset * sin(rRad);
	}
	pitch -= yOffset *cos(rRad) + xOffset * sin(rRad); // deltaRoll;

	if (!greaterThanNinety && pitch > 89.0f) {
		greaterThanNinety = true;
		//deltaRoll *= -1;
		cameraRotationPlaneUp *= -1;
		//pitch = (pitch - 89.0f) -89.0f;
	}
	else if (!greaterThanNinety && pitch < -89.0f) {
		greaterThanNinety = true;
		//deltaRoll *= -1;
		cameraRotationPlaneUp *= -1;
		//pitch = (pitch + 89.0f) + 89.0f;
	}
	else if(greaterThanNinety) {
		if (pitch <89.0f && pitch > -89.0f) {
			greaterThanNinety = false;
			cameraRotationPlaneUp *= -1;
		}
		else if (pitch > 180.0f) {
			pitch -= 360.0f;// - 180.0f;
		}
		else if (pitch < -180.0f) {
			pitch += 360.0f;
		}
	}


	UpdateCameraVectors();
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
		roll -= CameraSpeed * deltaTime * 100;
		UpdateCameraRotationVectors();
	}
	else if (direction == MovementDirection::ROLL_RIGHT) {
		roll += CameraSpeed * deltaTime * 100;
		UpdateCameraRotationVectors();
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

void FlyingCamera::UpdateCameraVectors()
{
	glm::vec3 front;
	float yRad = glm::radians(yaw), pRad = glm::radians(pitch);
	front.x = cos(yRad) * cos(pRad);
	front.y = sin(pRad);
	front.z = sin(yRad) * cos(pRad);

	cameraFront = glm::normalize(front);
	cameraRight = glm::normalize(glm::cross(cameraFront, cameraRotationPlaneUp));
	cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront)) * (float)deltaRoll;
}

void FlyingCamera::UpdateCameraRotationVectors()
{
	if (cameraFront == glm::vec3(0.0f)) {
		UpdateCameraVectors();
	}

	glm::mat4 rot = glm::rotate(glm::mat4(1.0), glm::radians(roll), cameraFront);

	cameraRotationPlaneUp = rot * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	cameraRight = glm::normalize(glm::cross(cameraFront, cameraRotationPlaneUp));
	cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}
