#pragma once

#include "Subsystem.h"

#include <vector>

enum class TickType
{
	Variable,
	Smooth
};

struct SubsystemWrapper
{
	SubsystemWrapper(const std::shared_ptr<Subsystem>& aSubsystem, TickType aTickGroup)
	{
		myPointer = aSubsystem;
		myTickGroup = aTickGroup;
	}

	std::shared_ptr<Subsystem> myPointer;
	TickType myTickGroup;
};

class EngineContext
{
public:
	EngineContext() = default;
	
	EngineContext::~EngineContext()
	{
		for (size_t i = mySubsystems.size() - 1; i > 0; i--)
		{
			mySubsystems[i].myPointer.reset();
		}

		mySubsystems.clear();
	}

	void Initialize()
	{
		for (const auto& subsystem : mySubsystems)
		{
			subsystem.myPointer->Initialize();
		}
	}

	void Tick(TickType aTickGroup, float aDeltaTime = 0.0f)
	{
		for (const auto& subsystem : mySubsystems)
		{
			if (subsystem.myTickGroup != aTickGroup)
				continue;

			subsystem.myPointer->Update(aDeltaTime);
		}
	}

	template <class Type>
	void RegisterSubsystem(TickType aTickGroup = TickType::Variable)
	{
		ValidateSubsystem<Type>();
		mySubsystems.emplace_back(std::make_shared<Type>(this), aTickGroup);
	}

	template <class Type>
	Type* GetSubsystem() const
	{
		ValidateSubsystem<Type>();

		for (const auto& subsystem : mySubsystems)
		{
			if (subsystem.myPointer)
			{
				if (typeid(Type) == typeid(*subsystem.myPointer))
					return static_cast<Type*>(subsystem.myPointer.get());
			}
		}

		return nullptr;
	}

private:
	std::vector<SubsystemWrapper> mySubsystems;
};