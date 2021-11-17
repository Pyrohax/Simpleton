#include "Entity.h"

Entity::Entity(Coordinator* aCoordinator)
	: myCoordinator(aCoordinator)
{
	myUID = myCoordinator->CreateEntity();
}

Entity::~Entity()
{
	delete myCoordinator;
}
