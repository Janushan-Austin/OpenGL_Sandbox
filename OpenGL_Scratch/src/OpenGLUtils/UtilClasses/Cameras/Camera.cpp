#include "Camera.h"

Camera::Camera(glm::vec3 pos, float fov, float y, float p, float r) : cameraPos(pos), yaw(y), pitch(p), roll(r), fov(fov), deltaRoll(1), cameraRotationPlaneUp(glm::vec3(0.0f, 1.0f, 0.0f)), cameraFront(0.0f), cameraRight(0.0f), cameraUp(0.0f)
{
}

Camera::~Camera()
{
}

glm::mat4 Camera::GenerateViewMatrix() {
	glm::vec3 front = glm::normalize(cameraFront);
	// point right hand fingers in direction of first vector then curl fingers towards other vector and thumb points in the direction the cross vector points
	glm::vec3 right = glm::normalize(glm::cross(front, cameraRotationPlaneUp));
	glm::vec3 up = (glm::cross(right, front));


	//return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraRotationPlaneUp);

	glm::mat4 result(1.0);

	result[0][0] = right.x; result[1][0] = right.y; result[2][0] = right.z; result[3][0] = -glm::dot(cameraPos, right);
	result[0][1] = up.x; result[1][1] = up.y; result[2][1] = up.z; result[3][1] = -glm::dot(cameraPos, up);
	result[0][2] = -front.x; result[1][2] = -front.y; result[2][2] = -front.z; result[3][2] = glm::dot(cameraPos, front);

	return result;
}