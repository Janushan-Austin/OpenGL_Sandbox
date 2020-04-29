#include "Camera.h"

Camera::Camera(glm::vec3 pos, float fov, float y, float p, float r) : cameraPos(pos), yaw(y), pitch(p), roll(r), fov(fov), cameraFront(0.0f, 0.0f, -1.0f), cameraRight(1.0f, 0.0f, 0.0f), cameraUp(0.0f, 1.0f, 0.0f)
{
	ApplyPitch(0.0f);
	ApplyYaw(0.0f);
	ApplyRoll(0.0f);
}

Camera::~Camera()
{
}

void Camera::ApplyPitch(float pitchOffset)
{
	pitch -= pitchOffset;
	cameraFront = glm::normalize((cameraFront * cosf(glm::radians(-pitchOffset))) + (cameraUp * sinf(glm::radians(-pitchOffset))));

	cameraUp = glm::cross(cameraRight, cameraFront);
}

void Camera::ApplyYaw(float yawOffset)
{
	yaw += yawOffset;
	cameraFront = glm::normalize((cameraFront * cosf(glm::radians(yawOffset))) + (cameraRight * sinf(glm::radians(yawOffset))));

	cameraRight = glm::cross(cameraFront, cameraUp);
}

void Camera::ApplyRoll(float rollOffset)
{
	roll += rollOffset;
	cameraRight = glm::normalize((cameraRight * cosf(glm::radians(rollOffset))) + (cameraUp * sinf(glm::radians(rollOffset))));

	cameraUp = glm::cross(cameraRight, cameraFront);
}

glm::mat4 Camera::GenerateViewMatrix() {
	//glm::vec3 front = glm::normalize(cameraFront);
	// point right hand fingers in direction of first vector then curl fingers towards other vector and thumb points in the direction the cross vector points
	//glm::vec3 right = glm::normalize(glm::cross(front, cameraRotationPlaneUp));
	//glm::vec3 up = (glm::cross(right, front));


	//return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraRotationPlaneUp);

	glm::mat4 result(1.0);

	result[0][0] = cameraRight.x; result[1][0] = cameraRight.y; result[2][0] = cameraRight.z; result[3][0] = -glm::dot(cameraPos, cameraRight);
	result[0][1] = cameraUp.x; result[1][1] = cameraUp.y; result[2][1] = cameraUp.z; result[3][1] = -glm::dot(cameraPos, cameraUp);
	result[0][2] = -cameraFront.x; result[1][2] = -cameraFront.y; result[2][2] = -cameraFront.z; result[3][2] = glm::dot(cameraPos, cameraFront);

	return result;
}