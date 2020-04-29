#pragma once
#include "Camera.h"
class FlyingFPSCamera :
	public Camera
{
public:
	FlyingFPSCamera(glm::vec3 pos = glm::vec3(0.0f), float fov = 90.0f, float y = 0.0f, float p = 0.0f, float r = 0.0f);
	~FlyingFPSCamera();

	// Inherited via Camera
	virtual void ProcessMouseMovement(float xOffset, float yOffset) override;
	virtual void ProcessKeyboardInput(MovementDirection direction, float deltaTime) override;
	virtual void ProcessMouseScroll(float yOffset) override;

protected:

	virtual void ApplyPitch(float pitchOffset) override;
	//virtual void ApplyPitch(float pitchOffset) override;
};

