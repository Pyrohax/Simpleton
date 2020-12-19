#pragma once

#include <vector>
#include <memory>

#include "SerializableData.h"

class DataManager
{
public:
	DataManager();
	~DataManager();

	void ReadData();

	template <class Type>
	Type* GetSerializableData() const
	{
		for (const auto& serializableData : mySerializableData)
		{
			if (serializableData.myPointer)
			{
				if (typeid(Type) == typeid(*serializableData.myPointer))
					return static_cast<Type*>(serializableData.myPointer.get());
			}
		}

		return nullptr;
	}

private:
	struct SerializableDataKeeper
	{
		SerializableDataKeeper(const std::shared_ptr<SerializableData>& aSerializableData)
		{
			myPointer = aSerializableData;
		}

		std::shared_ptr<SerializableData> myPointer;
	};

	template <class Type>
	void RegisterSerializableData()
	{
		mySerializableData.emplace_back(std::make_shared<Type>());
	}

private:
	std::vector<SerializableDataKeeper> mySerializableData;
};
