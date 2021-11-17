#pragma once

#include "System.h"
#include "Types.h"

#include <cassert>
#include <memory>
#include <unordered_map>

class SystemManager
{
public:
	template<typename T>
	std::shared_ptr<T> RegisterSystem()
	{
		const char* typeName = typeid(T).name();
		assert(mySystems.find(typeName) == mySystems.end() && "Registering system more than once.");
		auto system = std::make_shared<T>();
		mySystems.insert({typeName, system});
		return system;
	}

	template<typename T>
	void SetSignature(Signature aSignature)
	{
		const char* typeName = typeid(T).name();
		assert(mySystems.find(typeName) != mySystems.end() && "System used before registered.");
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
