#include "EntityComponentSystem.h"

#include "../Engine.h"
#include "../Component/TransformComponent.h"
#include "../Component/ModelComponent.h"
#include "../Utility/Assert.h"

#include <string>

const size_t MAX_COMPONENTS = 150;
const size_t MAX_ENTITIES = 150;

bool EntityComponentSystem::Init()
{
	myComponentTable.reserve(MAX_COMPONENTS);
	myComponentTypeTable.reserve(MAX_COMPONENTS);
	myEntityTable.reserve(MAX_ENTITIES);

	return true;
}

void EntityComponentSystem::Update(double aDeltaTime)
{
}

void EntityComponentSystem::Terminate()
{
	for (auto& i : myComponentTable)
		RemoveComponent(i.first);
}

void EntityComponentSystem::RemoveComponent(UniqueID aUID)
{
	switch (myComponentTypeTable[aUID])
	{
	case ComponentType::TRANSFORM:
		delete static_cast<TransformComponent*>(myComponentTable[aUID]);
		break;

	case ComponentType::MODEL:
		delete static_cast<ModelComponent*>(myComponentTable[aUID]);
		break;

	case ComponentType::UNDEFINED:
		Log::Print(LogType::PROBLEM, "Attempting to remove a nonexistent component. UID: ", std::to_string(aUID));
		return;

	default:
		Assert(true, "Remove component had invalid type! UID: ", std::to_string(aUID));
		return;
	}
	
	myComponentTypeTable[aUID] = ComponentType::UNDEFINED;
	return;
}
