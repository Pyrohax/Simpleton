#include "EngineContext.h"

EngineContext::~EngineContext()
{
	for (auto& subsystem : mySubsystems)
	{
		subsystem.myPointer.reset();
	}

	mySubsystems.clear();
}

void EngineContext::Initialize()
{
	for (const auto& subsystem : mySubsystems)
	{
		subsystem.myPointer->Initialize();
	}
}

void EngineContext::Tick(TickType aTickGroup, float aDeltaTime)
{
	for (const auto& subsystem : mySubsystems)
	{
		if (subsystem.myTickGroup != aTickGroup)
			continue;

		subsystem.myPointer->Update(aDeltaTime);
	}
}
