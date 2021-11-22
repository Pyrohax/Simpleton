#pragma once

#include "Types.h"
#include "Coordinator.h"

class Entity
{
public:
	Entity(const UID aUID, Coordinator* aCoordinator);
	~Entity();

	template<typename ComponentTemplate>
	void AddComponent(ComponentTemplate aComponent)
	{
		myCoordinator->AddComponent(myUID, aComponent);
	}

	template<typename ComponentTemplate>
	void RemoveComponent()
	{
		myCoordinator->RemoveComponent<ComponentTemplate>(myUID);
	}

	template<typename ComponentTemplate>
	ComponentTemplate& GetComponent()
	{
		return myCoordinator->GetComponent<ComponentTemplate>(myUID);
	}

	const UID GetUID() const { return myUID; }

private:
	Coordinator* myCoordinator;
	UID myUID;
};
