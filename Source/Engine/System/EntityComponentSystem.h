#pragma once

#include "../Core/TypeDefines.h"
#include "../Element/Component.h"
#include "../Element/Entity.h"

#include <string>
#include <algorithm>
#include <unordered_map>

enum class ComponentType
{
	UNDEFINED = 0,
	TRANSFORM = 1,
	MODEL = 2
};

class EntityComponentSystem
{
public:
	EntityComponentSystem();
	~EntityComponentSystem();

	void Initialize();
	void Update(double aDeltaTime);
	void Terminate();

	UniqueID AddEntity();
	void RemoveEntity(UniqueID aUID);

	template<typename T>
	UniqueID AddComponent()
	{
		static_assert(std::is_base_of<Component, T>::value);
		Component* component = new T;
		myComponentTable.emplace(myUIDCounter, component);
		myComponentTypeTable.emplace(myUIDCounter, GetTypeByComponentClass<T>());
		myUIDCounter += 1;
		return myUIDCounter - 1;
	}
	
	void RemoveComponent(UniqueID aUID);

	template<typename T>
	T* GetComponent(UniqueID aUID)
	{
		static_assert(std::is_base_of<Component, T>::value);
		return static_cast<T*>(myComponentTable[aUID]);
	}

	template<typename T>
	ComponentType GetTypeByComponentClass()
	{
		static_assert(std::is_base_of<Component, T>::value);
		if constexpr (std::is_same<T, TransformComponent>::value)
			return ComponentType::TRANSFORM;
		if constexpr (std::is_same<T, ModelComponent>::value)
			return ComponentType::MODEL;
		
		return ComponentType::UNDEFINED;
	}

	Entity* GetEntity(UniqueID aUID) { return myEntityTable[aUID]; }

protected:
	std::unordered_map<UniqueID, Component*> myComponentTable;
	std::unordered_map<UniqueID, ComponentType> myComponentTypeTable;
	std::unordered_map<UniqueID, Entity*> myEntityTable;
	UniqueID myUIDCounter;
};
