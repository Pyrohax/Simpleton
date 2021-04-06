#pragma once

#include <uuid.h>

#include <string>
#include <vector>

class EntityFactory;
struct Component;
struct MeshComponent;

class Entity
{
public:
	Entity(const std::string& aName, EntityFactory* anEntityFactory);
	~Entity();

	const uuids::uuid& GetUID() const { return myUID; }
	const std::string& GetName() const { return myName; }

	void AddComponent(Component* aComponent);
	MeshComponent* GetMesComponent() const;

private:
	EntityFactory* myEntityFactory;
	uuids::uuid myUID;
	std::string myName;
};
