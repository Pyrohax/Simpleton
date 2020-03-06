#pragma once

#include "JobSystem.h"

class Engine {
public:
	Engine();
	~Engine();

	bool Init();
	void Update();
	void Terminate();

	JobSystem myJobSystem;
};