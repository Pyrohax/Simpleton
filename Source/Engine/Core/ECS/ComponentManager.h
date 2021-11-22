#pragma once

#include "../EngineDefines.h"
#include "ComponentArray.h"

#include <any>
#include <memory>
#include <unordered_map>

class ComponentManager
{
public:
	template<typename ComponentTemplate>
	void RegisterComponent()
	{
		const char* typeName = typeid(ComponentTemplate).name();
		Assert(myComponentTypes.find(typeName) != myComponentTypes.end(), "Registering component type more than once.");
		myComponentTypes.insert({typeName, myNextComponentType});
		myComponentArrays.insert({typeName, std::make_shared<ComponentArray<ComponentTemplate>>()});
		++myNextComponentType;
	}

	template<typename ComponentTemplate>
	ComponentType GetComponentType()
	{
		const char* typeName = typeid(ComponentTemplate).name();
		Assert(myComponentTypes.find(typeName) == myComponentTypes.end(), "Component not registered before use.");
		return myComponentTypes[typeName];
	}

	template<typename ComponentTemplate>
	void AddComponent(const UID anEntityUID, ComponentTemplate aComponent)
	{
		GetComponentArray<ComponentTemplate>()->InsertData(anEntityUID, aComponent);
	}

	template<typename ComponentTemplate>
	void RemoveComponent(const UID anEntityUID)
	{
		GetComponentArray<ComponentTemplate>()->RemoveData(anEntityUID);
	}

	template<typename ComponentTemplate>
	ComponentTemplate& GetComponent(const UID anEntityUID)
	{
		return GetComponentArray<ComponentTemplate>()->GetData(anEntityUID);
	}

	template<typename ComponentTemplate>
	bool HasComponent(const UID anEntityUID) const
	{
		return GetComponentArray<ComponentTemplate>()->HasData(anEntityUID);
	}

	void EntityDestroyed(const UID anEntityUID);

private:
	std::unordered_map<const char*, ComponentType> myComponentTypes;
	std::unordered_map<const char*, std::shared_ptr<ComponentArrayBase>> myComponentArrays;
	ComponentType myNextComponentType;

	template<typename ComponentTemplate>
	std::shared_ptr<ComponentArray<ComponentTemplate>> GetComponentArray()
	{
		const char* typeName = typeid(ComponentTemplate).name();
		Assert(myComponentTypes.find(typeName) == myComponentTypes.end(), "Component not registered before use.");
		return std::static_pointer_cast<ComponentArray<ComponentTemplate>>(myComponentArrays[typeName]);
	}
};
