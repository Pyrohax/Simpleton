#pragma once

#include "Types.h"

#include <set>

class SystemBase
{
public:
	virtual void Update() = 0;

	std::set<UID> myEntities;
};
