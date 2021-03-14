#pragma once

class Entity;

class EntityFactory
{
public:
	EntityFactory();
	~EntityFactory();

	Entity* CreateEntity();

private:

};
