#include "ComponentManager.h"

void ComponentManager::EntityDestroyed(UID anEntityUID)
{
	for (auto const& pair : myComponentArrays)
	{
		auto const& component = pair.second;
		component->EntityDestroyed(anEntityUID);
	}
}
