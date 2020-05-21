#pragma once

#include "../Element/Component.h"

#include <string>
#include <algorithm>
#include <unordered_map>


enum class ComponentType
{
	UNDEFINED = 0,
	TRANSFORM = 1,
	MODEL = 2
};

typedef size_t UniqueID;

class EntityComponentSystem
{
public:
	EntityComponentSystem() : myUIDCounter(0) {};
	~EntityComponentSystem() {};

	bool Init();
	void Update(double aDeltaTime);
	void Terminate();

	template<typename T>
	UniqueID AddComponent()
	{
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
		return static_cast<T*>(myComponentTable[aUID]);
	}

	template<typename T>
	ComponentType GetTypeByComponentClass()
	{
		if constexpr (std::is_same<T, TransformComponent>::value)
			return ComponentType::TRANSFORM;
		if constexpr (std::is_same<T, ModelComponent>::value)
			return ComponentType::MODEL;
		
		return ComponentType::UNDEFINED;
	}

protected:
	std::unordered_map<UniqueID, Component*> myComponentTable;
	std::unordered_map<UniqueID, ComponentType> myComponentTypeTable;

	UniqueID myUIDCounter;
};


