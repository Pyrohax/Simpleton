#pragma once

#include "../EngineDefines.h"

class ComponentArrayBase
{
public:
	virtual ~ComponentArrayBase() = default;
	virtual void EntityDestroyed(const UID anEntityUID) = 0;
};
