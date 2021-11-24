#include "EntityManager.h"

#include "../../Core/Assert.h"
#include "Entity.h"
#include "EntityComponentSystem.h"

EntityManager::EntityManager()
	: myLivingEntitiesCount(0)
{
	for (UID entity = 0; entity < MAX_ENTITIES; ++entity)
		myAvailableEntities.push(entity);
}

Entity* EntityManager::CreateEntity(EntityComponentSystem* aEntityComponentSystem)
{
	Assert(myLivingEntitiesCount > MAX_ENTITIES, "Too many entities in existence.");
	UID uid = myAvailableEntities.front();
	myAvailableEntities.pop();
	++myLivingEntitiesCount;
	return new Entity(uid, aEntityComponentSystem);
}

void EntityManager::DestroyEntity(const UID anEntityUID)
{
	Assert(anEntityUID > MAX_ENTITIES, "Entity out of range.");
	mySignatures[anEntityUID].reset();
	myAvailableEntities.push(anEntityUID);
	--myLivingEntitiesCount;
}

void EntityManager::SetSignature(const UID anEntityUID, const EntitySignature aSignature)
{
	Assert(anEntityUID > MAX_ENTITIES, "Entity out of range.");
	mySignatures[anEntityUID] = aSignature;
}

EntitySignature EntityManager::GetSignature(const UID anEntityUID) const
{
	Assert(anEntityUID > MAX_ENTITIES, "Entity out of range.");
	return mySignatures[anEntityUID];
}
