#include "EntityComponentSystem.h"

#include "../Core/Assert.h"
#include "../Core/Engine.h"
#include "TransformComponent.h"
#include "ModelComponent.h"

#include <string>

const size_t MAX_COMPONENTS = 150;
const size_t MAX_ENTITIES = 150;

EntityComponentSystem::EntityComponentSystem()
	: myUIDCounter(0)
{
}

EntityComponentSystem::~EntityComponentSystem()
{
}

void EntityComponentSystem::Initialize()
{
	myComponentTable.reserve(MAX_COMPONENTS);
	myComponentTypeTable.reserve(MAX_COMPONENTS);
	myEntityTable.reserve(MAX_ENTITIES);
}

void EntityComponentSystem::Update(double aDeltaTime)
{
}

void EntityComponentSystem::Terminate()
{
	for (auto& component : myComponentTable)
		RemoveComponent(component.first);
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

UniqueID EntityComponentSystem::AddEntity()
{
	Entity* entity = new Entity;
	myEntityTable.emplace(myUIDCounter, entity);
	myUIDCounter += 1;
	return myUIDCounter - 1;
}

void EntityComponentSystem::RemoveEntity(UniqueID aUID)
{
	Entity*& entity = myEntityTable[aUID];
	if (!entity)
		return;

	delete entity;
	entity = nullptr;
}
