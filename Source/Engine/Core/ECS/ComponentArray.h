#pragma once

#include "../../Core/Assert.h"
#include "ComponentArrayBase.h"

#include <array>
#include <unordered_map>

template<typename ComponentTemplate>
class ComponentArray final : public ComponentArrayBase
{
public:
	void InsertData(const UID anEntityUID, ComponentTemplate aComponent)
	{
		Assert(myEntityToIndexMap.find(anEntityUID) != myEntityToIndexMap.end(), "Component added to same entity more than once.");
		size_t newIndex = mySize;
		myEntityToIndexMap[anEntityUID] = newIndex;
		myIndexToEntityMap[newIndex] = anEntityUID;
		myComponentArray[newIndex] = aComponent;
		++mySize;
	}

	void RemoveData(const UID anEntityUID)
	{
		Assert(myEntityToIndexMap.find(anEntityUID) == myEntityToIndexMap.end(), "Removing non-existent component.");
		size_t indexOfRemovedEntity = myEntityToIndexMap[anEntityUID];
		size_t indexOfLastElement = mySize - 1;
		myComponentArray[indexOfRemovedEntity] = myComponentArray[indexOfLastElement];
		UID entityOfLastElement = myIndexToEntityMap[indexOfLastElement];
		myEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
		myIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;
		myEntityToIndexMap.erase(anEntityUID);
		myIndexToEntityMap.erase(indexOfLastElement);
		--mySize;
	}

	ComponentTemplate& GetData(const UID anEntityUID)
	{
		Assert(myEntityToIndexMap.find(anEntityUID) == myEntityToIndexMap.end(), "Retrieving non-existent component.");
		return myComponentArray[myEntityToIndexMap[anEntityUID]];
	}

	void EntityDestroyed(const UID anEntityUID) override
	{
		if (myEntityToIndexMap.find(anEntityUID) != myEntityToIndexMap.end())
			RemoveData(anEntityUID);
	}

private:
	std::array<ComponentTemplate, MAX_ENTITIES> myComponentArray;
	std::unordered_map<UID, size_t> myEntityToIndexMap;
	std::unordered_map<size_t, UID> myIndexToEntityMap;
	size_t mySize;
};
