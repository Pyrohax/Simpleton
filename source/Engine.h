#pragma once

#include "JobSystem.h"
#include "Subsystem/EntityComponentSystem.h"

class Engine {
public:
	Engine();
	~Engine();

	bool Init();
	void Update();
	void Terminate();

	JobSystem myJobSystem;
	EntityComponentSystem myEntityComponentSystem;
};