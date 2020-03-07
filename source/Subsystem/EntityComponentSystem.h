#pragma once

#include "../Element/Entity.h"
#include "../Component/TransformComponent.h"

#include <string>

class Engine;

class EntityComponentSystem
{
public:
	EntityComponentSystem(Engine* aEngine) : myEngine(aEngine) {};
	~EntityComponentSystem() {};

	bool Init();
	void Update(double dt);
	void Terminate();

	Entity* CreateEntity(std::string aName = "Unnamed Entity");
	Entity* GetEntity(std::string aName);
	void DestroyEntity(Entity* aEntity);

	template<class T>
	Component* CreateComponent(Entity* aEntity)
	{
		Component* componentToAdd = static_cast<Component*>(new T(aEntity));
		return componentToAdd;
	};

	void AddComponent(Component* aComponent)
	{
		// Deduce type and add it to the correct component list
		if (dynamic_cast<TransformComponent*>(aComponent) != nullptr)
			myTransformComponents.push_back(static_cast<TransformComponent*>(aComponent));
			
		// if(dynamic_cast<\new type\>(aComponent)
		//		\new type list\.push_back(static_cast<\new type\*>(aComponent));
	}
	
	Engine* myEngine;

protected:
	void CleanRemovedEntities();
	void AddEntity(Entity* aEntity);
	Entity* RemoveEntity(Entity* aEntity);

	std::vector<Entity*> myEntityList;
	std::vector<TransformComponent*> myTransformComponents;
};


