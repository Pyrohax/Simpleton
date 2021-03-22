#pragma once

#include <uuid.h>

#include <vector>
#include <string>

class Entity
{
public:
	Entity(const std::string& aName);
	~Entity();

	const uuids::uuid& GetUID() const { return myUID; }
	const std::string& GetName() const { return myName; }

private:
	uuids::uuid myUID;
	std::string myName;
};
