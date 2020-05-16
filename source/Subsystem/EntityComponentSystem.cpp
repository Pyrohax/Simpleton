#include "EntityComponentSystem.h"

#include "../Engine.h"

#include <algorithm>

bool EntityComponentSystem::Init()
{

	return true;
}

void EntityComponentSystem::Update(double aDeltaTime)
{
	glm::mat4 m1(2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2);
	glm::mat4 m2(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4);
	glm::mat4 m3(6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6);
	glm::mat4 m4(8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8);

	TransformComponent& t1 = AddComponent<TransformComponent>(m1);
	TransformComponent& t2 = AddComponent<TransformComponent>(m2);
	TransformComponent& t3 = AddComponent<TransformComponent>(m3);
	TransformComponent& t4 = AddComponent<TransformComponent>(m4);

	myMoveSystem.MoveAll(glm::vec3(100, 100, 100));
	myMoveSystem.MoveAll(glm::vec3(100, 100, 100));
	myMoveSystem.MoveAll(glm::vec3(100, 100, 100));

	//RemoveComponent<TransformComponent>(t2);
	//RemoveComponent<TransformComponent>(t3); 
	//RemoveComponent<TransformComponent>(t1);
	//RemoveComponent<TransformComponent>(t4);
	return;
}

void EntityComponentSystem::Terminate()
{

}