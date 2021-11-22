#pragma once

#include "Types.h"

#include <array>
#include <queue>

class Entity;
class Coordinator;

class EntityManager
{
public:
	EntityManager();

	Entity* CreateEntity(Coordinator* aCoordinator);
	void DestroyEntity(const UID anEntityUID);
	void SetSignature(const UID anEntityUID, Signature aSignature);
	Signature GetSignature(const UID anEntityUID) const;

private:
	std::queue<UID> myAvailableEntities;
	std::array<Signature, MAX_ENTITIES> mySignatures;
	uint32_t myLivingEntitiesCount;
};
