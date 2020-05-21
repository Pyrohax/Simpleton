#include "EntityComponentSystem.h"

#include "../Engine.h"

#include <algorithm>

const size_t MAX_COMPONENTS = 150;

bool EntityComponentSystem::Init()
{
	myComponentTable.reserve(MAX_COMPONENTS);
	UniqueID uid = AddComponent<TransformComponent>();
	GetComponent<TransformComponent>(uid);
	RemoveComponent<TransformComponent>(uid);
	
	return true;
}

void EntityComponentSystem::Update(double aDeltaTime)
{
}

void EntityComponentSystem::Terminate()
{
}