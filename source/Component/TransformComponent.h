#pragma once
#include "../Element/Component.h"
#include "../../dependencies/glm/glm/glm.hpp"

class TransformComponent : public Component
{
public:
	TransformComponent(Entity* anOwner) : Component(anOwner), myTransform(glm::mat4x4()) {};
	~TransformComponent() {};

	bool Update() { return true; };
	void Destroy() {};

	glm::mat4x4 myTransform;
};