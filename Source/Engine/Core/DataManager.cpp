#include "DataManager.h"

#include "EngineSettings.h"

DataManager::DataManager()
{
	RegisterSerializableData<EngineSettings>();
}

DataManager::~DataManager()
{
}

void DataManager::ReadData()
{
	for (const auto& serializableData : mySerializableData)
	{
		if (serializableData.myPointer)
		{
			serializableData.myPointer.get()->Deserialize();
		}
	}
}
