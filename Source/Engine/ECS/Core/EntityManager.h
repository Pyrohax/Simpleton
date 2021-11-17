#pragma once

#include "Types.h"

#include <array>
#include <cassert>
#include <queue>

class EntityManager
{
public:
	EntityManager();

	UID CreateEntity();
	void DestroyEntity(UID anEntityUID);
	void SetSignature(UID anEntityUID, Signature aSignature);
	Signature GetSignature(UID anEntityUID) const;

private:
	std::queue<UID> myAvailableEntities;
	std::array<Signature, MAX_ENTITIES> mySignatures;
	uint32_t myLivingEntitiesCount;
};
