#include "Entity.h"

#include "Coordinator.h"

Entity::Entity(const UID aUID, Coordinator* aCoordinator)
	: myCoordinator(aCoordinator)
	, myUID(aUID)
{}

Entity::~Entity()
{
	myCoordinator->DestroyEntity(myUID);
	delete myCoordinator;
}
