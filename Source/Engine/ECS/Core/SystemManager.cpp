#include "SystemManager.h"

void SystemManager::Update()
{
	for (std::pair<const char* const, std::shared_ptr<SystemBase>>& system : mySystems)
		system.second->Update();
}
