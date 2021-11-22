#include "EntityComponentSystem.h"

#include "CameraComponent.h"
#include "LightingComponent.h"
#include "MeshComponent.h"
#include "TransformComponent.h"

EntityComponentSystem::EntityComponentSystem()
{
	myComponentManager = std::make_unique<ComponentManager>();
	myEntityManager = std::make_unique<EntityManager>();
	mySystemManager = std::make_unique<EntitySystemManager>();
}

EntityComponentSystem::~EntityComponentSystem()
{
	mySystemManager.reset();
	myEntityManager.reset();
	myComponentManager.reset();
}

void EntityComponentSystem::Initialize()
{
	RegisterComponent<TransformComponent>();
	RegisterComponent<CameraComponent>();
	RegisterComponent<LightingComponent>();
	RegisterComponent<MeshComponent>();
}

Entity* EntityComponentSystem::CreateEntity()
{
	return myEntityManager->CreateEntity(this);
}

void EntityComponentSystem::DestroyEntity(const UID anEntityUID)
{
	myEntityManager->DestroyEntity(anEntityUID);
	myComponentManager->EntityDestroyed(anEntityUID);
	mySystemManager->EntityDestroyed(anEntityUID);
}
