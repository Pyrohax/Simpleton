#pragma once

#include <glm/mat4x4.hpp>

class CameraComponent
{
public:
	CameraComponent();
	~CameraComponent() = default;

	void Update(const float aDeltaTime);

	const glm::mat4x4& GetProjectionMatrix() const { return myProjection; }
	const glm::mat4x4& GetViewMatrix() const { return myView; }
	const glm::vec3& GetPositionMatrix() const { return myPosition; }
	const glm::vec3& GetPosition() const { return myPosition; }
	const glm::vec3& GetFront() const { return myFront; }
	const glm::vec3& GetRight() const { return myRight; }
	const glm::vec3& GetUp() const { return myUp; }
	const glm::vec3& GetDirection() const { return myDirection; }

	const float GetFieldOfView() const { return myFieldOfView; }
	const float GetHorizontalAngle() const { return myHorizontalAngle; }
	const float GetVerticalAngle() const { return myVerticalAngle; }

private:
	glm::mat4 myProjection;
	glm::mat4 myView;
	glm::vec3 myPosition;
	glm::vec3 myFront;
	glm::vec3 myRight;
	glm::vec3 myUp;
	glm::vec3 myDirection;
	float myHorizontalAngle;
	float myVerticalAngle;
	float myDefaultFieldOfView;
	float myFieldOfView;
	float myMouseSpeed;
	float myKeySpeed;
	float myKeyBoostMultiplier;
};
