#include "ComponentManager.h"

void ComponentManager::EntityDestroyed(const UID anEntityUID)
{
	for (const std::pair<const char*, std::shared_ptr<ComponentArrayBase>>& pair : myComponentArrays)
	{
		auto const& component = pair.second;
		component->EntityDestroyed(anEntityUID);
	}
}
