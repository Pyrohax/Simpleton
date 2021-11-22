#pragma once

#include "../../Core/Assert.h"
#include "EntitySystemBase.h"

#include <memory>
#include <unordered_map>

class EntitySystemManager
{
public:
	void Update();

	template<typename SystemTemplate>
	std::shared_ptr<SystemTemplate> RegisterSystem()
	{
		const char* typeName = typeid(SystemTemplate).name();
		Assert(myEntitySystems.find(typeName) != myEntitySystems.end(), "Registering system more than once.");
		auto entitySystem = std::make_shared<SystemTemplate>();
		myEntitySystems.insert({ typeName, entitySystem });
		return entitySystem;
	}

	template<typename SignatureTemplate>
	void SetSignature(EntitySignature aSignature)
	{
		const char* typeName = typeid(SignatureTemplate).name();
		Assert(myEntitySystems.find(typeName) == myEntitySystems.end(), "System used before registered.");
		mySignatures.insert({ typeName, aSignature });
	}

	void EntityDestroyed(const UID anEntityUID);
	void EntitySignatureChanged(const UID anEntityUID, const EntitySignature anEntitySignature);

private:
	std::unordered_map<const char*, EntitySignature> mySignatures;
	std::unordered_map<const char*, std::shared_ptr<EntitySystemBase>> myEntitySystems;
};
