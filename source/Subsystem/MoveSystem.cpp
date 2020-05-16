#include "MoveSystem.h"

void MoveSystem::MoveAll(glm::vec3 aMove)
{
	for (auto& i : myTransformComponentList)
	{
		i.SetPos(i.GetPos() + aMove);
	}
};