#pragma once
class Entity;

class Component
{
public:
	Component(Entity* anOwner) : myOwner(anOwner) {};
	~Component() {};
	Entity* myOwner;

	virtual bool Update() = 0;
	virtual void Destroy() = 0;
};