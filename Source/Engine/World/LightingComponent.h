#pragma once

#include "Component.h"

#include <glm/vec3.hpp>

struct LightingComponent : public Component
{
public:
	LightingComponent();
	LightingComponent(const glm::vec3& aColor);

	void SetColor(const glm::vec3& aColor) { myColor = aColor; }

	const glm::vec3& GetColor() const { return myColor; }

private:
	glm::vec3 myColor;
};
