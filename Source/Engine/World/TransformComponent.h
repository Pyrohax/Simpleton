#pragma once

#include "Component.h"

#include <glm/vec3.hpp>

struct TransformComponent : public Component
{
public:
	TransformComponent();
	TransformComponent(const glm::vec3& aPosition);

	void SetPosition(const glm::vec3& aPosition) { myPosition = aPosition; }

	const glm::vec3& GetPosition() const { return myPosition; }

private:
	glm::vec3 myPosition;
};
