#pragma once

#include "ComponentManager.h"
#include "EntityManager.h"
#include "SystemManager.h"

#include <memory>

class Entity;

class Coordinator
{
public:
	Coordinator();
	~Coordinator();

	void Initialize();

	Entity* CreateEntity();
	void DestroyEntity(UID anEntityUID);

	template<typename ComponentTemplate>
	void RegisterComponent()
	{
		myComponentManager->RegisterComponent<ComponentTemplate>();
	}

	template<typename ComponentTemplate>
	void AddComponent(UID anEntityUID, ComponentTemplate aComponent)
	{
		myComponentManager->AddComponent<ComponentTemplate>(anEntityUID, aComponent);
		auto signature = myEntityManager->GetSignature(anEntityUID);
		signature.set(myComponentManager->GetComponentType<ComponentTemplate>(), true);
		myEntityManager->SetSignature(anEntityUID, signature);
		mySystemManager->EntitySignatureChanged(anEntityUID, signature);
	}

	template<typename ComponentTemplate>
	void RemoveComponent(UID anEntityUID)
	{
		myComponentManager->RemoveComponent<ComponentTemplate>(anEntityUID);
		auto signature = myEntityManager->GetSignature(anEntityUID);
		signature.set(myComponentManager->GetComponentType<ComponentTemplate>(), false);
		myEntityManager->SetSignature(anEntityUID, signature);
		mySystemManager->EntitySignatureChanged(anEntityUID, signature);
	}

	template<typename ComponentTemplate>
	ComponentTemplate& GetComponent(UID anEntityUID)
	{
		return myComponentManager->GetComponent<ComponentTemplate>(anEntityUID);
	}

	template<typename ComponentTemplate>
	ComponentType GetComponentType()
	{
		return myComponentManager->GetComponentType<ComponentTemplate>();
	}

	template<typename SystemTemplate>
	std::shared_ptr<SystemTemplate> RegisterSystem()
	{
		return mySystemManager->RegisterSystem<SystemTemplate>();
	}

	template<typename SystemSignatureTemplate>
	void SetSystemSignature(Signature aSignature)
	{
		mySystemManager->SetSignature<SystemSignatureTemplate>(aSignature);
	}

private:
	std::unique_ptr<ComponentManager> myComponentManager;
	std::unique_ptr<EntityManager> myEntityManager;
	std::unique_ptr<SystemManager> mySystemManager;
};
