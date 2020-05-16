#pragma once
#include "../../dependencies/glm/glm/glm.hpp"

// Memory aligned component.

class TransformComponent
{
public:
	TransformComponent() : myTransform(glm::mat4x4()) {};
	TransformComponent(glm::mat4x4 aTransform) : myTransform(aTransform) {};

	~TransformComponent() {};

	bool Update() { return true; };
	void Destroy() {};

	glm::vec3 GetPos();
	void SetPos(glm::vec3 aPosition);

	glm::vec3 GetForward();
	
	inline bool operator==(const TransformComponent& right)
	{
		if (myTransform == right.myTransform)
			return true;
		else 
			return false;
	}
	inline bool operator!=(const TransformComponent& right) 
	{
		return !(*this == right);
	}

private:
	glm::mat4x4 myTransform;
};