#pragma once

#include <memory>

class EngineContext;

class Subsystem : public std::enable_shared_from_this<Subsystem>
{
public:
	Subsystem(EngineContext* aContext) { myContext = aContext; }
	virtual ~Subsystem() = default;
	virtual void Initialize() = 0;
	virtual void Update(const float aDeltaTime) = 0;
	virtual void Terminate() = 0;

	template<typename Type>
	std::shared_ptr<Type> GetSharedPointer() { return std::dynamic_pointer_cast<Type>(shared_from_this()); }

protected:
	EngineContext* myContext;
};

template<typename Type>
constexpr void ValidateSubsystem() { static_assert(std::is_base_of<Subsystem, Type>::value, "Provided type does not implement Subsystem"); }
