#pragma once

#include <vector>

class Entity;

class EntityFactory
{
public:
	EntityFactory();
	~EntityFactory();

	Entity* CreateEntity();
	int GetEntityCount() const { return static_cast<int>(myEntities.size()); }
	Entity* GetEntityByIndex(const int anIndex) { return &myEntities[anIndex]; }

private:
	std::vector<Entity> myEntities;
};
