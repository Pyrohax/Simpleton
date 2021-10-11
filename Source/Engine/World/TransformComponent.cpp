#include "TransformComponent.h"

TransformComponent::TransformComponent()
	: myPosition(0.0f)
	, myRotation(0.0f)
	, myScale(1.0f)
{
}

TransformComponent::TransformComponent(const glm::vec3& aPosition)
	: myPosition(aPosition)
	, myRotation(0.0f)
	, myScale(1.0f)
{
}
