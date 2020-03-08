#pragma once
class Entity;

class Component
{
public:
	Component(Entity* anOwner) : myOwner(anOwner) {};
	virtual ~Component() {};
	Entity* myOwner;

	virtual bool Update() = 0;
	virtual void Destroy() = 0;
};