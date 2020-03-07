#pragma once
class Entity;

//! Base component class. This indicates the structure for all other components.
class Component
{
public:
	Component();
	Component(Entity* _owner);
	~Component();

	//! Owner is a reference to which this component is attached to.
	Entity* owner;

	virtual void Update();
	virtual void Destroy();
};