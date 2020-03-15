#pragma once

#include "JobSystem.h"
#include "Subsystem/EntityComponentSystem.h"

class Yellowstone;

class Engine {
public:
	Engine();
	~Engine();

	bool Init();
	void Update();
	void Terminate();

	Yellowstone* YellowstoneInstance();

	JobSystem myJobSystem;
	EntityComponentSystem myEntityComponentSystem;

private:
	Yellowstone* myYellowstone;
};

extern Yellowstone* YellowstoneInstance();