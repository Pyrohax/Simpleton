#pragma once

#include "../Element/Entity.h"

#include <string>

class EntityComponentSystem
{
public:
	EntityComponentSystem() {};
	~EntityComponentSystem() {};

	bool Init();
	void Update(double dt);
	void Terminate();

	Entity* CreateEntity(std::string aName = "Unnamed Entity");
	Entity* GetEntity(std::string aName);
	void DestroyEntity(Entity* aEntity);

protected:
	void CleanRemovedEntities();
	void AddEntity(Entity* aEntity);
	Entity* RemoveEntity(Entity* aEntity);

	std::vector<Entity*> myEntityList;
};