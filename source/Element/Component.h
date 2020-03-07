#pragma once
class Entity;

class Component
{
public:
	Component(Entity* anOwner) : myOwner(anOwner) {};

	Entity* myOwner;

	virtual void Update() = 0;
	virtual void Destroy() = 0;
};