#pragma once

#include "../EngineDefines.h"

#include <set>

class EntitySystemBase
{
public:
	virtual void Update() = 0;

	std::set<UID> myEntities;
};
