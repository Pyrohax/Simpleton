#include "Entity.h"

Entity::Entity(EntityFactory* anEntityFactory, entt::entity aHandle)
	: myEntityFactory(anEntityFactory)
	, myEntityHandle(aHandle)
{
}

Entity::~Entity()
{
	delete myEntityFactory;
}
