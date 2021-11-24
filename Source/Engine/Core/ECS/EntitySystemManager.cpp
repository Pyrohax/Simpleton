#include "EntitySystemManager.h"

void EntitySystemManager::Update()
{
	for (std::pair<const char* const, std::shared_ptr<EntitySystemBase>>& system : myEntitySystems)
		system.second->Update();
}

void EntitySystemManager::EntityDestroyed(const UID anEntityUID)
{
	for (const std::pair<const char*, std::shared_ptr<EntitySystemBase>>& pair : myEntitySystems)
		pair.second->myEntities.erase(anEntityUID);
}

void EntitySystemManager::EntitySignatureChanged(const UID anEntityUID, const EntitySignature anEntitySignature)
{
	for (const std::pair<const char*, std::shared_ptr<EntitySystemBase>>& pair : myEntitySystems)
	{
		auto const& systemSignature = mySignatures[pair.first];
		if ((anEntitySignature & systemSignature) == systemSignature)
		{
			pair.second->myEntities.insert(anEntityUID);
		}
		else
		{
			pair.second->myEntities.erase(anEntityUID);
		}
	}
}
