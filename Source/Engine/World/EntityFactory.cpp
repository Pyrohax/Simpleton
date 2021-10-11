#include "EntityFactory.h"

#include "../Core/Assert.h"
#include "Entity.h"

EntityFactory::EntityFactory()
{
}

EntityFactory::~EntityFactory()
{
}

Entity* EntityFactory::CreateEntity()
{
	Entity* entity = new Entity(this, myRegistry.create());
	return entity;
}
