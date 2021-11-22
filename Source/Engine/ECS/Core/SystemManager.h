#pragma once

#include "../../Core/Assert.h"
#include "System.h"
#include "Types.h"

#include <memory>
#include <unordered_map>

class SystemManager
{
public:
	void Update();

	template<typename SystemTemplate>
	std::shared_ptr<SystemTemplate> RegisterSystem()
	{
		const char* typeName = typeid(SystemTemplate).name();
		Assert(mySystems.find(typeName) != mySystems.end(), "Registering system more than once.");
		auto system = std::make_shared<SystemTemplate>();
		mySystems.insert({typeName, system});
		return system;
	}

	template<typename SignatureTemplate>
	void SetSignature(Signature aSignature)
	{
		const char* typeName = typeid(SignatureTemplate).name();
		Assert(mySystems.find(typeName) == mySystems.end(), "System used before registered.");
		mySignatures.insert({typeName, aSignature });
	}

	void EntityDestroyed(const UID anEntityUID)
	{
		for (const std::pair<const char*, std::shared_ptr<SystemBase>>& pair : mySystems)
			pair.second->myEntities.erase(anEntityUID);
	}

	void EntitySignatureChanged(const UID anEntityUID, const Signature anEntitySignature)
	{
		for (const std::pair<const char*, std::shared_ptr<SystemBase>>& pair : mySystems)
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

private:
	std::unordered_map<const char*, Signature> mySignatures;
	std::unordered_map<const char*, std::shared_ptr<SystemBase>> mySystems;
};
