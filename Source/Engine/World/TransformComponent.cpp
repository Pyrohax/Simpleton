#include "TransformComponent.h"

TransformComponent::TransformComponent()
	: myPosition(0.0f)
{
}

TransformComponent::TransformComponent(const glm::vec3& aPosition)
	: myPosition(aPosition)
{
}
