#pragma once

#include "../Element/Entity.h"
#include "../Component/TransformComponent.h"
#include "../Utility/Logger.h"

#include <string>
#include <algorithm>

class Engine;

class EntityComponentSystem
{
public:
	EntityComponentSystem(Engine* aEngine) : myEngine(aEngine) {};
	~EntityComponentSystem() {};

	bool Init();
	void Update(double aDeltaTime);
	void Terminate();

	Entity* CreateEntity(std::string aName = "Unnamed Entity");
	Entity* GetEntity(std::string aName);
	void DestroyEntity(Entity* aEntity);

	template<class T>
	Component* CreateComponent(Entity* aEntity)
	{
		Component* componentToAdd = static_cast<Component*>(new T(aEntity));
		aEntity->myComponents.push_back(componentToAdd);
		return componentToAdd;
	};

	void AddComponent(Component* aComponent)
	{
		// Deduce type and add it to the correct component list
		if (TransformComponent* component = dynamic_cast<TransformComponent*>(aComponent))
			myTransformComponents.push_back(component);
			
		//if(/*new type*/component = dynamic_cast</*new type*/>(aComponent))
		//	/*new type list*/.push_back</*new type*/*>(aComponent);
	}
	
	void DestroyComponent(Component* aComponent)
	{
		if (!aComponent)
		{
			Log::Print("Attempted to destroy nullptr component!", LogType::WARNING);
			return;
		}
		
		auto isComponentToRemove = [&aComponent](Component* aComponentToCompare) -> bool { return aComponentToCompare == aComponent; };
		
		Entity* owner = aComponent->myOwner;

		if (owner)
			owner->myComponents.erase(std::remove_if(owner->myComponents.begin(), owner->myComponents.end(), isComponentToRemove), owner->myComponents.end());

		if (TransformComponent* component = dynamic_cast<TransformComponent*>(aComponent))
		{
			if (aComponent == component)
			{
				const size_t componentAmount = myTransformComponents.size();
				myTransformComponents.erase(std::remove_if(myTransformComponents.begin(), myTransformComponents.end(), isComponentToRemove), myTransformComponents.end());
				if (componentAmount == myTransformComponents.size())
					Log::Print("Attempted to delete component never added to their component list! (Forgot to call AddComponent?)", LogType::WARNING);
				delete aComponent;
			}
		}
	};

	Engine* myEngine;
	
protected:
	void CleanRemovedEntities();
	void AddEntity(Entity* aEntity);
	Entity* RemoveEntity(Entity* aEntity);

	std::vector<Entity*> myEntityList;
	std::vector<TransformComponent*> myTransformComponents;
};


