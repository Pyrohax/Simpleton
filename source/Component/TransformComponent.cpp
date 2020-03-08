#include "TransformComponent.h"

glm::vec3 TransformComponent::GetPos()
{
	return glm::vec3(myTransform[3][0], myTransform[3][1], myTransform[3][2]);
}

void TransformComponent::SetPos(glm::vec3 aPosition)
{
	myTransform[3][0] = aPosition.x;
	myTransform[3][1] = aPosition.y;
	myTransform[3][2] = aPosition.z;
	return;
}

glm::vec3 TransformComponent::GetForward()
{
	return glm::vec3(myTransform[2][0], myTransform[2][1], myTransform[2][2]);
}