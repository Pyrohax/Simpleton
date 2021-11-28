#include "EngineContext.h"

EngineContext::~EngineContext()
{
	for (auto& subsystem : mySubsystems)
		subsystem.myPointer.reset();

	mySubsystems.clear();
}

void EngineContext::Initialize()
{
	for (const auto& subsystem : mySubsystems)
		subsystem.myPointer->Initialize();
}

void EngineContext::Update(const TickType aTickGroup, const float aDeltaTime)
{
	for (const auto& subsystem : mySubsystems)
	{
		if (subsystem.myTickGroup != aTickGroup)
			continue;

		subsystem.myPointer->Update(aDeltaTime);
	}
}

void EngineContext::Terminate()
{
	for (const auto& subsystem : mySubsystems)
		subsystem.myPointer->Terminate();
}
