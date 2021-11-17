#include "Coordinator.h"

#include "../../World/CameraComponent.h"
#include "../../World/LightingComponent.h"
#include "../../World/MeshComponent.h"
#include "../../World/TransformComponent.h"
#include "../Systems/PhysicsSystem.h"

Coordinator::Coordinator()
{
	myComponentManager = std::make_unique<ComponentManager>();
	myEntityManager = std::make_unique<EntityManager>();
	mySystemManager = std::make_unique<SystemManager>();
}

Coordinator::~Coordinator()
{
	mySystemManager.reset();
	myEntityManager.reset();
	myComponentManager.reset();
}

void Coordinator::Initialize()
{
	RegisterComponent<TransformComponent>();
	RegisterComponent<CameraComponent>();
	RegisterComponent<LightingComponent>();
	RegisterComponent<MeshComponent>();

	auto physicsSystem = RegisterSystem<PhysicsSystem>();

	Signature signature;
	signature.set(GetComponentType<TransformComponent>());
	SetSystemSignature<PhysicsSystem>(signature);
}

UID Coordinator::CreateEntity()
{
	return myEntityManager->CreateEntity();
}

void Coordinator::DestroyEntity(UID anEntityUID)
{
	myEntityManager->DestroyEntity(anEntityUID);
	myComponentManager->EntityDestroyed(anEntityUID);
	mySystemManager->EntityDestroyed(anEntityUID);
}
