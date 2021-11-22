#pragma once

#include "Types.h"

#include <array>
#include <cassert>
#include <queue>

class Entity;
class Coordinator;

class EntityManager
{
public:
	EntityManager();

	Entity* CreateEntity(Coordinator* aCoordinator);
	void DestroyEntity(UID anEntityUID);
	void SetSignature(UID anEntityUID, Signature aSignature);
	Signature GetSignature(UID anEntityUID) const;

private:
	std::queue<UID> myAvailableEntities;
	std::array<Signature, MAX_ENTITIES> mySignatures;
	uint32_t myLivingEntitiesCount;
};
