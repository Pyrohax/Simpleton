#include "EntityManager.h"

EntityManager::EntityManager()
	: myLivingEntitiesCount(0)
{
	for (UID entity = 0; entity < MAX_ENTITIES; ++entity)
		myAvailableEntities.push(entity);
}

UID EntityManager::CreateEntity()
{
	assert(myLivingEntitiesCount < MAX_ENTITIES && "Too many entities in existence.");
	UID uid = myAvailableEntities.front();
	myAvailableEntities.pop();
	++myLivingEntitiesCount;
	return uid;
}

void EntityManager::DestroyEntity(UID anEntityUID)
{
	assert(anEntityUID < MAX_ENTITIES && "Entity out of range.");
	mySignatures[anEntityUID].reset();
	myAvailableEntities.push(anEntityUID);
	--myLivingEntitiesCount;
}

void EntityManager::SetSignature(UID anEntityUID, Signature aSignature)
{
	assert(anEntityUID < MAX_ENTITIES && "Entity out of range.");
	mySignatures[anEntityUID] = aSignature;
}

Signature EntityManager::GetSignature(UID anEntityUID) const
{
	assert(anEntityUID < MAX_ENTITIES && "Entity out of range.");
	return mySignatures[anEntityUID];
}
