#pragma once
#include <vector>

#include "../Component/TransformComponent.h"

class MoveSystem 
{
public:
	MoveSystem(std::vector<TransformComponent>& aTransformComponentList) : myTransformComponentList(aTransformComponentList) {	};

	void MoveAll(glm::vec3 aMove);
	
	std::vector<TransformComponent>& myTransformComponentList;
};