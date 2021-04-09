#pragma once

#include <unordered_map>
#include <uuid.h>
#include <vector>

const size_t MAX_COMPONENTS = 150;
const size_t MAX_ENTITIES = 150;

struct Component;
class Entity;

class EntityFactory
{
public:
	EntityFactory();
	~EntityFactory();

	void CreateEntity();
	void CreateEntity(const std::string& aName);
	
	void AddComponent(const uuids::uuid& anEntityUID, Component* aComponent);

	template<class ComponentType>
	ComponentType* GetComponent(const uuids::uuid& anEntityUID) const
	{
		for (auto& hash : myComponents)
		{
			if (hash.first != anEntityUID)
				continue;

			ComponentType* component = static_cast<ComponentType*>(hash.second);
			if (!component)
				continue;

			return component;
		}

		return nullptr;
	}

	int GetEntityCount() const { return static_cast<int>(myEntities.size()); }
	Entity& GetEntityByIndex(const int anIndex);
	const Entity& GetEntityByUID(const uuids::uuid& anUID) const;

private:
	std::unordered_map<uuids::uuid, Component*> myComponents;
	std::vector<Entity> myEntities;
};
