#pragma once

#include <entt/entt.hpp>

const size_t MAX_COMPONENTS = 150;
const size_t MAX_ENTITIES = 150;

class Entity;

class EntityFactory
{
public:
	EntityFactory();
	~EntityFactory();

	Entity* CreateEntity();

	template<typename ComponentType, typename... Args>
	ComponentType& AddComponent(const entt::entity& anEntity, Args &&... anArguments)
	{
		return myRegistry.emplace<ComponentType>(anEntity, std::forward<Args>(anArguments)...);
	}

	template<typename ComponentType>
	ComponentType& GetComponent(const entt::entity& anEntity)
	{
		return myRegistry.get<ComponentType>(anEntity);
	}

	template<typename ComponentType>
	ComponentType& GetComponent(const entt::entity& anEntity) const
	{
		return myRegistry.get<ComponentType>(anEntity);
	}

	template<typename ComponentType>
	bool HasComponent(const entt::entity& anEntity) const
	{
		return (myRegistry.try_get<ComponentType>(anEntity));
	}

	template<typename ComponentType, typename... Args>
	void RemoveComponent(const entt::entity& anEntity, Args &&... anArguments)
	{
		myRegistry.remove<ComponentType>(anEntity);
	}

private:
	entt::registry myRegistry;
};
