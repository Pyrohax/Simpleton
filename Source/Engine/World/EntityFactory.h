#pragma once

#include <vector>
#include <uuid.h>

class Entity;

const size_t MAX_COMPONENTS = 150;
const size_t MAX_ENTITIES = 150;

class EntityFactory
{
public:
	EntityFactory();
	~EntityFactory();

	void CreateEntity();
	int GetEntityCount() const { return static_cast<int>(myEntities.size()); }
	Entity& GetEntityByIndex(const int anIndex);
	const Entity& GetEntityByUID(const uuids::uuid& anUID) const;

private:
	std::vector<Entity> myEntities;
};
