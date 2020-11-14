#pragma once

#include "Component.h"

#include <vector>
#include <string>

class Entity
{
public:
	Entity() {};
	~Entity() {};

	std::string myName;
	std::vector<unsigned int> myComponentIDList;
};