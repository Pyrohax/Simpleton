#include "LightingComponent.h"

LightingComponent::LightingComponent()
	: myColor(1.0f, 1.0f, 1.0f)
{
}

LightingComponent::LightingComponent(const glm::vec3& aColor)
	: myColor(aColor)
{
}
