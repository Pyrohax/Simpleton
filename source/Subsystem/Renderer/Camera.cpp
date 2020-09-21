#include "Camera.h"

#include "InputManager.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

Camera::Camera()
{
	myProjection = glm::perspective(glm::radians(45.0f), 1240.0f / 720.0f, 0.1f, 100.0f);
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

	myView = glm::lookAt(myPosition, myPosition + myFront, myUp);
}

const glm::mat4x4 Camera::GetModelViewMatrix() const
{
	return myProjection * myView;
}
