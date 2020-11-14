#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Camera
{
public:
	Camera();
	~Camera();

	void Update(float aDeltaTime);
	void DrawDebug();

	const glm::mat4x4& GetProjectionMatrix() const { return myProjection; }
	const glm::mat4x4& GetViewMatrix() const { return myView; }
	const glm::vec3& GetPositionMatrix() const { return myPosition; }

private:
	glm::mat4 myProjection;
	glm::mat4 myView;
	glm::vec3 myPosition;
	glm::vec3 myFront;
	glm::vec3 myRight;
	glm::vec3 myUp;
	float myHorizontalAngle;
	float myVerticalAngle;
	float myDefaultFieldOfView;
	float myFieldOfView;
	float myMouseSpeed;
	float myKeySpeed;
	float myKeyBoostMultiplier;
};
