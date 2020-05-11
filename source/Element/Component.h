#pragma once
class Entity;

class Component
{
public:
	Component(Entity* anOwner) : myOwner(anOwner) {};
	~Component() {};
	Entity* myOwner;
};