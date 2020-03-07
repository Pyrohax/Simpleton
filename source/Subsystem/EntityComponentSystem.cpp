#include "EntityComponentSystem.h"

#include "../Engine.h"

#include <algorithm>

bool EntityComponentSystem::Init()
{
	return true;
}

void EntityComponentSystem::Update(double dt)
{
	for (auto& i : myTransformComponents)
	{
		// Theoretical example on how we'd run specific functions multithreaded.
		auto func = std::bind(&TransformComponent::Update, i);
		myEngine->myJobSystem.AddJob(func);
	}

	CleanRemovedEntities();
}

void EntityComponentSystem::Terminate()
{
	for (Entity*& entity : myEntityList)
	{
		if (!entity)
			continue;
		delete(entity);
		entity = nullptr;
		entity;
	}
	CleanRemovedEntities();
}

Entity* EntityComponentSystem::CreateEntity(std::string aName)
{
	Entity* entity = new Entity();
	entity->myName = aName;

	myEntityList.push_back(entity);

	return entity;
}

Entity* EntityComponentSystem::GetEntity(std::string aName)
{
	for (Entity*& entity : myEntityList)
	{
		if (!entity)
			continue;
		else if (aName == entity->myName)
			return entity;
	}
	return nullptr;
}

void EntityComponentSystem::DestroyEntity(Entity* aEntity)
{
	for (Entity*& entity : myEntityList)
	{
		if (!entity)
			continue;
		else if (aEntity->myName == entity->myName)
		{
			delete entity;
			entity = nullptr;
		}
	}
}

void EntityComponentSystem::CleanRemovedEntities()
{
	myEntityList.erase(std::remove_if(myEntityList.begin(), myEntityList.end(), [](Entity*& e) -> bool {return e == nullptr;}), myEntityList.end());
	myEntityList.shrink_to_fit();
}

void EntityComponentSystem::AddEntity(Entity* aEntity)
{
	myEntityList.push_back(aEntity);
}

Entity* EntityComponentSystem::RemoveEntity(Entity* aEntity)
{
	Entity* removedEntity = nullptr;
	for (Entity* entity : myEntityList)
	{
		if (!entity)
			continue;
		else if (aEntity->myName == entity->myName)
		{
			removedEntity = entity;
			entity = nullptr;
			return removedEntity;
		}
	}
	return nullptr;
}

