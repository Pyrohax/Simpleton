#pragma once

#include "../EngineDefines.h"

#include <array>
#include <queue>

class Entity;
class EntityComponentSystem;

class EntityManager
{
public:
	EntityManager();

	Entity* CreateEntity(EntityComponentSystem* aEntityComponentSystem);
	void DestroyEntity(const UID anEntityUID);
	void SetSignature(const UID anEntityUID, const EntitySignature aSignature);
	EntitySignature GetSignature(const UID anEntityUID) const;

private:
	std::queue<UID> myAvailableEntities;
	std::array<EntitySignature, MAX_ENTITIES> mySignatures;
	uint32_t myLivingEntitiesCount;
};
