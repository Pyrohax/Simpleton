#pragma once

#include "Subsystem/JobSystem.h"
#include "Subsystem/EntityComponentSystem.h"

class Renderer;

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
	Renderer* myRenderer;
};
