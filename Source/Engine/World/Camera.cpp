#include "Camera.h"

#include "imgui.h"
#include "../Graphics/OpenGL/InputManager.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

Camera::Camera()
	: myHorizontalAngle(3.14f)
	, myVerticalAngle(0.0f)
	, myDefaultFieldOfView(45.0f)
	, myFieldOfView(myDefaultFieldOfView)
	, myMouseSpeed(0.01f)
	, myKeySpeed(2.5f)
	, myKeyBoostMultiplier(2.0f)
{
	myProjection = glm::perspective(glm::radians(myFieldOfView), 1280.0f / 720.0f, 0.1f, 100.0f);
	myPosition = glm::vec3(4.0f, 3.0f, 3.0f);
	myFront = glm::vec3(0.0f, 0.0f, -1.0f);
	myRight = glm::vec3(1.0f, 0.0f, 0.0f);
	myUp = glm::vec3(0.0f, 1.0f, 0.0f);
	myView = glm::lookAt(myPosition, myPosition + myFront, myUp);
	myDirection = glm::vec3(0.0f, 0.0f, 0.0f);
}

Camera::~Camera()
{
}

void Camera::Update(float aDeltaTime)
{
	const InputManager& inputManager = InputManager::GetInstance();

	float movementSpeed = myKeySpeed;

	if (inputManager.GetIsKeyDown(Keys::LeftShift))
		movementSpeed *= myKeyBoostMultiplier;

	if (inputManager.GetIsKeyDown(Keys::W))
		myPosition += aDeltaTime * movementSpeed * myFront;

	if (inputManager.GetIsKeyDown(Keys::A))
		myPosition -= aDeltaTime * movementSpeed * glm::normalize(glm::cross(myFront, myUp));

	if (inputManager.GetIsKeyDown(Keys::S))
		myPosition -= aDeltaTime * movementSpeed * myFront;

	if (inputManager.GetIsKeyDown(Keys::D))
		myPosition += aDeltaTime * movementSpeed * glm::normalize(glm::cross(myFront, myUp));

	if (inputManager.GetIsKeyDown(Keys::Spacebar))
		myPosition += aDeltaTime * movementSpeed * myUp;

	if (inputManager.GetIsKeyDown(Keys::LeftControl))
		myPosition -= aDeltaTime * movementSpeed * myUp;

	if (inputManager.GetIsMouseButtonDown(MouseButtons::Right))
	{
		myHorizontalAngle += aDeltaTime * myMouseSpeed * (1280.0f / 2.0f - inputManager.myCursorXPosition);
		myVerticalAngle += aDeltaTime * myMouseSpeed * (720.0f / 2.0f - inputManager.myCursorYPosition);
	}
	
	myDirection = glm::vec3(cos(myVerticalAngle) * sin(myHorizontalAngle), sin(myVerticalAngle), cos(myVerticalAngle) * cos(myHorizontalAngle));
	myRight = glm::vec3(sin(myHorizontalAngle - 3.14f / 2.0f), 0.0f, cos(myHorizontalAngle - 3.14f / 2.0f));
	myUp = glm::cross(myRight, myDirection);
	myFront = glm::normalize(myDirection);
	myFieldOfView = myDefaultFieldOfView - 5.0f * inputManager.myScrollYOffset;

	myProjection = glm::perspective(glm::radians(myFieldOfView), 1280.0f / 720.0f, 0.1f, 100.0f);
	myView = glm::lookAt(myPosition, myPosition + myDirection, myUp);
}

void Camera::DrawDebug()
{
	ImGui::Text("Front x:%0.f y:%0.f z:%0.f", myFront.x, myFront.y, myFront.z);
	ImGui::Text("Up x:%0.f y:%0.f z:%0.f", myUp.x, myUp.y, myUp.z);
	ImGui::Text("Right x:%0.f y:%0.f z:%0.f", myRight.x, myRight.y, myRight.z);
	ImGui::Text("FOV: %0.f", myDefaultFieldOfView);
	ImGui::Text("Position x:%f y:%f z:%f", myPosition.x, myPosition.y, myPosition.z);
	ImGui::Text("Direction x:%f y:%f z:%f", myDirection.x, myDirection.y, myDirection.z);
}
