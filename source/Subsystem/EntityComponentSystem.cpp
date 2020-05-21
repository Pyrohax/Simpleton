#include "EntityComponentSystem.h"

#include "../Engine.h"
#include "../Component/TransformComponent.h"
#include "../Component/ModelComponent.h"
#include "../Utility/Assert.h"

#include <algorithm>

const size_t MAX_COMPONENTS = 150;

bool EntityComponentSystem::Init()
{
	myComponentTable.reserve(MAX_COMPONENTS);
	myComponentTypeTable.reserve(MAX_COMPONENTS);

	UniqueID uid1 = AddComponent<TransformComponent>();
	UniqueID uid2 = AddComponent<ModelComponent>();

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
		myComponentTypeTable[aUID] = ComponentType::UNDEFINED;
		return;

	case ComponentType::MODEL:
		delete static_cast<ModelComponent*>(myComponentTable[aUID]);
		myComponentTypeTable[aUID] = ComponentType::UNDEFINED;
		return;

	case ComponentType::UNDEFINED:
		Log::Print(std::string("Double delete. Remove Component called on a already deleted component, UID: ").append(std::to_string(aUID)), LogType::PROBLEM);
		return;

	default:
		Assert(true, std::string("Remove component had invalid type! UID: ").append(std::to_string(aUID)));
		return;
	}
}
