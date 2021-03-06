#pragma once
#include "../Element/Component.h"
#include "../../dependencies/glm/glm/glm.hpp"

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