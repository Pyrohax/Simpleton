#pragma once

#include "JobSystem.h"
#include "Subsystem/EntityComponentSystem.h"
#include "Renderer/Yellowstone.h"

class Yellowstone;

class Engine {
public:
	Engine();
	~Engine();

	bool Init();
	void Update();
	void Terminate();

	JobSystem myJobSystem;
	EntityComponentSystem myEntityComponentSystem;

private:
	Yellowstone myYellowstone;

};