#pragma once

#include "../EngineDefines.h"
#include "EntityComponentSystem.h"

class Entity
{
public:
	Entity(const UID aUID, EntityComponentSystem* aEntityComponentSystem);
	~Entity();

	template<typename ComponentTemplate>
	void AddComponent(ComponentTemplate aComponent)
	{
		myEntityComponentSystem->AddComponent(myUID, aComponent);
	}

	template<typename ComponentTemplate>
	void RemoveComponent()
	{
		myEntityComponentSystem->RemoveComponent<ComponentTemplate>(myUID);
	}

	template<typename ComponentTemplate>
	ComponentTemplate& GetComponent()
	{
		return myEntityComponentSystem->GetComponent<ComponentTemplate>(myUID);
	}

	const UID GetUID() const { return myUID; }

private:
	EntityComponentSystem* myEntityComponentSystem;
	UID myUID;
};
