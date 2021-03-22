#include "EntityFactory.h"

#include "Entity.h"

#include "../Core/Assert.h"

EntityFactory::EntityFactory()
{
}

EntityFactory::~EntityFactory()
{
}

void EntityFactory::CreateEntity()
{
	Assert(myEntities.size() > MAX_ENTITIES, "The entity limit has been reached");
	Entity* entity = new Entity("Test");
	myEntities.push_back(*entity);
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
