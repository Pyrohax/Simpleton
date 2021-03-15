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
	Entity* entity = new Entity("Test");
	myEntities.push_back(*entity);

	return entity;
}
