#include "EntityFactory.h"

#include "../Core/Assert.h"
#include "Entity.h"
#include "MeshComponent.h"
#include "LightingComponent.h"

EntityFactory::EntityFactory()
{
}

EntityFactory::~EntityFactory()
{
}

void EntityFactory::CreateEntity()
{
	Assert(myEntities.size() > MAX_ENTITIES, "The entity limit has been reached");
	std::random_device randomDevice;
	std::mt19937 mersenneTwisterGenerator(randomDevice());
	std::uniform_int_distribution<std::mt19937::result_type> distribution(1, 256);
	std::string name = "Unnamed" + std::to_string(distribution(mersenneTwisterGenerator));
	Entity* entity = new Entity(name, this);
	myEntities.push_back(*entity);
}

void EntityFactory::CreateEntity(const std::string& aName)
{
	Assert(myEntities.size() > MAX_ENTITIES, "The entity limit has been reached");
	Entity* entity = new Entity(aName, this);
	myEntities.push_back(*entity);
}

void EntityFactory::AddComponent(const uuids::uuid& anEntityUID, Component* aComponent)
{
	myComponents.emplace(anEntityUID, aComponent);
}

Entity& EntityFactory::GetEntityByIndex(const int anIndex)
{
	Assert(anIndex > MAX_ENTITIES, "Entity index out of range");
	return myEntities[anIndex];
}

const Entity& EntityFactory::GetEntityByUID(const uuids::uuid& anUID) const
{
	for (const Entity& entity : myEntities)
	{
		if (entity.GetUID() == anUID)
		{
			return entity;
		}
	}
}
