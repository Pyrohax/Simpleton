#include "EntityFactory.h"

#include "../ECS/Entity.h"

EntityFactory::EntityFactory()
{
}

EntityFactory::~EntityFactory()
{
}

Entity* EntityFactory::CreateEntity()
{
	Entity* entity = new Entity();
	entity->myName = "test";

	return entity;
}
