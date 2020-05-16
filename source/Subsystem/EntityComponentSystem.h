#pragma once
#include "../Utility/Logger.h"
#include "../Utility/Assert.h"

#include "MoveSystem.h"

#include <string>
#include <algorithm>
#include <vector>

class Engine;

#define MAX_COMPONENT_SIZE 50

class EntityComponentSystem
{
public:
	// System funcionality
	EntityComponentSystem(Engine* aEngine) : myEngine(aEngine), myMoveSystem(myTransformComponents) 
	{
		myTransformComponents.reserve(MAX_COMPONENT_SIZE);
	};
	~EntityComponentSystem() {};

	bool Init();
	void Update(double aDeltaTime);
	void Terminate();

	Engine* myEngine;

	template<typename T, typename ... Args>
	T& AddComponent(Args... aParametersList)
	{
		// Add one of these for each component here.
		if constexpr (std::is_same<T, TransformComponent>::value)
		{
			return myTransformComponents.emplace_back(aParametersList...);
		}
	}

	template<typename T>
	bool RemoveComponent(T& aComponent)
	{
		// Add one of these for each component here.
		if constexpr (std::is_same<T, TransformComponent>::value)
		{
			for (size_t i = 0; i < myTransformComponents.size(); i++)
			{
				if (myTransformComponents[i] == aComponent)
				{
					myTransformComponents.erase(myTransformComponents.begin() + i);
					return true;
				}
			}
		}
		Assert(true, "Component was not in the system! Impossible. The archives were incomplete.");
		return false;
	}

	MoveSystem myMoveSystem;

protected:

private:
	std::vector<TransformComponent> myTransformComponents;
};

