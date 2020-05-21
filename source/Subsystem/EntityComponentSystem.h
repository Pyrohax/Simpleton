#pragma once

#include "../Element/Entity.h"
#include "../Component/TransformComponent.h"
#include "../Utility/Assert.h"

#include <string>
#include <algorithm>
#include <unordered_map>

typedef size_t UniqueID;

class EntityComponentSystem
{
public:
	EntityComponentSystem() : myComponentCounter(0) {};
	~EntityComponentSystem() {};

	bool Init();
	void Update(double aDeltaTime);
	void Terminate();

	template<typename T>
	UniqueID AddComponent()
	{
		Component* component = new T;
		myComponentTable.emplace(myComponentCounter, component);
		myComponentCounter += 1;
		return myComponentCounter - 1;
	}
	
	template<typename T>
	void RemoveComponent(UniqueID aUID)
	{
		if constexpr (std::is_same<T, TransformComponent>::value)
		{
			delete static_cast<TransformComponent*>(myComponentTable[aUID]);
			return;
		}
		
		Log::Print("MEMORY LEAK! Wrong type passed into RemoveComponent for the following UID :", LogType::WARNING);
		Assert(true, aUID);
		myComponentTable[aUID];
	}

	template<typename T>
	T* GetComponent(UniqueID aUID)
	{
		return static_cast<T*>(myComponentTable[aUID]);
	}

protected:
	std::unordered_map<UniqueID, Component*> myComponentTable;

	UniqueID myComponentCounter;
};


