#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
	: myProjection(0.0f)
	, myView(0.0f)
	, myFront(0.0f)
	, myUp(0.0f)
	, myPosition(0.0f)
	, myRight(0.0f)
{
}

Camera::~Camera()
{
}

void Camera::Update()
{
	myView = glm::lookAt(myPosition, myPosition + myFront, myUp);
}
