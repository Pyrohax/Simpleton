#pragma once

#include "EntityFactory.h"

#include <uuid.h>

#include <string>
#include <vector>

class Entity
{
public:
	Entity(const std::string& aName, EntityFactory* anEntityFactory);
	~Entity();

	const uuids::uuid& GetUID() const { return myUID; }
	const std::string& GetName() const { return myName; }

	void AddComponent(Component* aComponent);

	template<class ComponentType>
	ComponentType* GetComponent() const
	{
		return myEntityFactory->GetComponent<ComponentType>(myUID);
	}

private:
	EntityFactory* myEntityFactory;
	uuids::uuid myUID;
	std::string myName;
};
