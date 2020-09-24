#include "Camera.h"

#include "InputManager.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

Camera::Camera()
	: myHorizontalAngle(3.14f)
	, myVerticalAngle(0.0f)
	, myDefaultFieldOfView(45.0f)
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

void Camera::Update()
{
	if (InputManager::GetInstance().GetIsKeyDown(Keys::W))
		myPosition += 0.05f * myFront;

	if (InputManager::GetInstance().GetIsKeyDown(Keys::A))
		myPosition -= 0.05f * myRight;

	if (InputManager::GetInstance().GetIsKeyDown(Keys::S))
		myPosition -= 0.05f * myFront;

	if (InputManager::GetInstance().GetIsKeyDown(Keys::D))
		myPosition += 0.05f * myRight;

	if (InputManager::GetInstance().GetIsKeyDown(Keys::Spacebar))
		myPosition += 0.05f * myUp;

	if (InputManager::GetInstance().GetIsKeyDown(Keys::LeftShift))
		myPosition -= 0.05f * myUp;

	myHorizontalAngle += 0.05f * 0.0016f * (1280.0f / 2 - InputManager::GetInstance().myCursorXPosition);
	myVerticalAngle += 0.05f * 0.0016f * (720.0f / 2 - InputManager::GetInstance().myCursorYPosition);
	
	glm::vec3 direction(cos(myVerticalAngle) * sin(myHorizontalAngle), sin(myVerticalAngle), cos(myVerticalAngle) * cos(myHorizontalAngle));
	myRight = glm::vec3(sin(myHorizontalAngle - 3.14f / 2.0f), 0, cos(myHorizontalAngle - 3.14f / 2.0f));
	myUp = glm::cross(myRight, direction);
	float fieldOfView = myDefaultFieldOfView - 5.0f * InputManager::GetInstance().myScrollYOffset;

	myProjection = glm::perspective(glm::radians(fieldOfView), 1280.0f / 720.0f, 0.1f, 100.0f);
	myView = glm::lookAt(myPosition, myPosition + direction, myUp);
}

const glm::mat4x4 Camera::GetViewProjectionMatrix() const
{
	return myProjection * myView;
}
