#pragma once

#include <unordered_map>
#include <uuid.h>
#include <vector>

class Entity;

const size_t MAX_COMPONENTS = 150;
const size_t MAX_ENTITIES = 150;

struct Component;
struct MeshComponent;

class EntityFactory
{
public:
	EntityFactory();
	~EntityFactory();

	void CreateEntity();
	void CreateEntity(const std::string& aName);
	
	void AddComponent(const uuids::uuid& anEntityUID, Component* aComponent);
	MeshComponent* GetMeshComponent(const uuids::uuid& anEntityUID) const;

	int GetEntityCount() const { return static_cast<int>(myEntities.size()); }
	Entity& GetEntityByIndex(const int anIndex);
	const Entity& GetEntityByUID(const uuids::uuid& anUID) const;

private:
	std::unordered_map<uuids::uuid, Component*> myComponents;
	std::vector<Entity> myEntities;
};
