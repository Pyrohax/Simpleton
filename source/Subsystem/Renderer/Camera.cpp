#include "Camera.h"

#include "InputManager.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

Camera::Camera()
	: myHorizontalAngle(3.14f)
	, myVerticalAngle(0.0f)
	, myDefaultFieldOfView(45.0f)
	, myMouseSensitivity(0.2f)
{
	myProjection = glm::perspective(glm::radians(myDefaultFieldOfView), 1240.0f / 720.0f, 0.1f, 100.0f);
	myPosition = glm::vec3(4, 3, 3);
	myFront = glm::vec3(0, 0, -1);
	myRight = glm::vec3(1, 0, 0);
	myUp = glm::vec3(0, 1, 0);
	myView = glm::lookAt(myPosition, myPosition + myFront, myUp);
}

Camera::~Camera()
{
}

void Camera::Update(double aDeltaTime)
{
	const InputManager& inputManager = InputManager::GetInstance();
	if (inputManager.GetIsKeyDown(Keys::W))
		myPosition += 0.05f * myFront;

	if (inputManager.GetIsKeyDown(Keys::A))
		myPosition -= 0.05f * myRight;

	if (inputManager.GetIsKeyDown(Keys::S))
		myPosition -= 0.05f * myFront;

	if (inputManager.GetIsKeyDown(Keys::D))
		myPosition += 0.05f * myRight;

	if (inputManager.GetIsKeyDown(Keys::Spacebar))
		myPosition += 0.05f * myUp;

	if (inputManager.GetIsKeyDown(Keys::LeftShift))
		myPosition -= 0.05f * myUp;

	if (inputManager.GetIsKeyDown(Keys::LeftControl))
	{
		myHorizontalAngle += 0.05f * aDeltaTime * myMouseSensitivity * (1280.0f / 2 - inputManager.myCursorXPosition);
		myVerticalAngle += 0.05f * aDeltaTime * myMouseSensitivity * (720.0f / 2 - inputManager.myCursorYPosition);
	}
	
	glm::vec3 direction(cos(myVerticalAngle) * sin(myHorizontalAngle), sin(myVerticalAngle), cos(myVerticalAngle) * cos(myHorizontalAngle));
	myRight = glm::vec3(sin(myHorizontalAngle - 3.14f / 2.0f), 0, cos(myHorizontalAngle - 3.14f / 2.0f));
	myUp = glm::cross(myRight, direction);
	float fieldOfView = myDefaultFieldOfView - 5.0f * inputManager.myScrollYOffset;

	myProjection = glm::perspective(glm::radians(fieldOfView), 1280.0f / 720.0f, 0.1f, 100.0f);
	myView = glm::lookAt(myPosition, myPosition + direction, myUp);
}
