#pragma once

#include "../Element/Entity.h"
#include "../Component/TransformComponent.h"
#include "../Utility/Logger.h"
#include "../Utility/Assert.h"

#include <string>
#include <algorithm>

class Engine;

class EntityComponentSystem
{
public:
	///////////////////////////////////////////////////////////////
	// System funcionality
	///////////////////////////////////////////////////////////////
	EntityComponentSystem(Engine* aEngine) : myEngine(aEngine) {};
	~EntityComponentSystem() {};

	bool Init();
	void Update(double aDeltaTime);
	void Terminate();


	///////////////////////////////////////////////////////////////
	// Entity funcitonality
	///////////////////////////////////////////////////////////////
	Entity* CreateEntity(std::string aName = "Unnamed Entity");
	Entity* GetEntity(std::string aName);
	void DestroyEntity(Entity* aEntity);


	///////////////////////////////////////////////////////////////
	// Component functionality
	///////////////////////////////////////////////////////////////
	template<typename T, typename ... Args>
	T* AddComponent(Entity* aOwner, Args... aArguments)
	{
		static_assert(std::is_base_of<Component, T>::value, "Trying to add a component that does not inherit from the Component class.");

		if (!aOwner)
			return nullptr;

		T* addedComponent = nullptr;
		// Add one of these every time you create a new component.
		if constexpr (std::is_same<T, TransformComponent>::value)
			addedComponent = &myTransformComponents.emplace_back(aOwner, aArguments...);

		else if constexpr (std::is_same<T, Component>::value)
			addedComponent = &myTestComponents.emplace_back(aOwner, aArguments...);

		Assert(!addedComponent, "No constructor implemented for component input type.");

		aOwner->myComponents.push_back(addedComponent);
		return addedComponent;
	}

	template<typename T>
	bool DestroyComponent(Component* aComponent)
	{
		if (!aComponent)
			return false;

		if (Entity* owner = aComponent->myOwner)
		{
			std::vector<Component*>& ownerComponents = owner->myComponents;
			const size_t listSize = ownerComponents.size();
			for (size_t i = listSize; i > 0; --i)
			{
				if (aComponent == ownerComponents[i - 1])
					ownerComponents.erase(ownerComponents.begin() + i - 1);
			}
		}

		// Add one of these for each, in order of amount of times used.
		if constexpr (std::is_same<T, TransformComponent>::value)
			return DestructComponent<TransformComponent>(static_cast<TransformComponent*>(aComponent), myTransformComponents);

		else if constexpr (std::is_same<T, Component>::value)
		{
			return DestructComponent<Component>(static_cast<Component*>(aComponent), myTestComponents);
			Log::Print("Adding a base component should only be used for testing!", LogType::WARNING);
		}

		Log::Print("Removed a component from an owner but no system was found to remove it from. Wrong input type?", LogType::WARNING);
		return false;
	}
	
	Engine* myEngine;
	
protected:

private:
	void CleanRemovedEntities();

	template <typename T>
	bool DestructComponent(T* aComponent, std::vector<T>& aComponentList)
	{
		const size_t listSize = aComponentList.size();
		for (size_t i = listSize; i > 0; --i)
		{
			if (aComponent == &aComponentList[i - 1])
			{
				aComponentList.erase(aComponentList.begin() + i - 1);
				return true;
			}
		}
		Assert(true, "Deleting a component that doesn't exist in the list. The archives are incomplete.");
		return false;
	}

	std::vector<Entity*> myEntityList;
	std::vector<Component> myTestComponents;
	std::vector<TransformComponent> myTransformComponents;
};


