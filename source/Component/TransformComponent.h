#pragma once
#include "../Element/Component.h"
#include "../../dependencies/glm/glm/glm.hpp"
#include "../Utility/Logger.h"

class TransformComponent : public Component
{
public:
	TransformComponent() : myTransform(glm::mat4x4()) {};
	~TransformComponent() {};

	bool Update() { return true; };

	glm::vec3 GetPos();
	void SetPos(glm::vec3 aPosition);

	glm::vec3 GetForward();
	
private:
	glm::mat4x4 myTransform;
};