#include "Entity.h"

Entity::Entity(const UID aUID, EntityComponentSystem* aEntityComponentSystem)
	: myEntityComponentSystem(aEntityComponentSystem)
	, myUID(aUID)
{}

Entity::~Entity()
{
	myEntityComponentSystem->DestroyEntity(myUID);
	delete myEntityComponentSystem;
}
