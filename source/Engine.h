#pragma once

#include "Subsystem/JobSystem.h"
#include "Subsystem/EntityComponentSystem.h"

class Yellowstone;

class Engine
{
public:
	Engine();
	~Engine();

	bool Init();
	void Update();
	void Terminate();

	JobSystem myJobSystem;
	EntityComponentSystem myEntityComponentSystem;

private:
	Yellowstone* myYellowstone;
};
