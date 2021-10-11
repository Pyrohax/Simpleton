#pragma once

#include "../Core/Assert.h"
#include "EntityFactory.h"

#include <entt/entt.hpp>

#include <uuid.h>

class Entity
{
public:
	Entity() = default;
	Entity(const Entity& anOther) = default;
	Entity(EntityFactory* anEntityFactory, entt::entity aHandle);
	~Entity();

	template<typename T, typename... Args>
	T& AddComponent(Args&&... args)
	{
		myEntityFactory->AddComponent<T>(myEntityHandle, std::forward<Args>(args)...);
	}

	template<typename T>
	T& GetComponent()
	{
		return myEntityFactory->GetComponent<T>(myEntityHandle);
	}

	template<typename T>
	void RemoveComponent()
	{
		return myEntityFactory->RemoveComponent<T>(myEntityHandle);
	}

	operator bool() const { return myEntityHandle != entt::null; }
	operator entt::entity() const { return myEntityHandle; }
	operator uint32_t() const { return static_cast<uint32_t>(myEntityHandle); }

	bool operator==(const Entity& other) const
	{
		return myEntityHandle == other.myEntityHandle && mySceneUID == other.mySceneUID;
	}

	bool operator!=(const Entity& anOther) const
	{
		return !(*this == anOther);
	}

	const entt::entity& GetEntityHandle() const { return myEntityHandle; }

private:
	EntityFactory* myEntityFactory;
	entt::entity myEntityHandle{ entt::null };
	uuids::uuid mySceneUID;
};
