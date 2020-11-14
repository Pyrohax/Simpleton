#pragma once

#include "Component.h"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class TransformComponent : public Component
{
public:
	TransformComponent() : myTransform(glm::mat4x4()) {};
	~TransformComponent() {};

	glm::vec3 GetPos();
	void SetPos(glm::vec3 aPosition);

	glm::vec3 GetForward();
	
private:
	glm::mat4x4 myTransform;
};