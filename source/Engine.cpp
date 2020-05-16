#include "Engine.h"
#include <windows.h>

#undef AddJob

Engine::Engine() : myEntityComponentSystem(this) {}

Engine::~Engine() {}

auto exampleJob = []() -> bool
{
	Sleep(100);

	return true;
};

bool Engine::Init()
{
	myJobSystem.Init();
	myEntityComponentSystem.Init();
	return false;
}

void Engine::Update()
{
	myEntityComponentSystem.Update(0.0f);
	return;
}

void Engine::Terminate()
{
	myJobSystem.Terminate();
	myEntityComponentSystem.Terminate();
}