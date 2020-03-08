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
	// Leaving this in to show as a good example.
	Entity* e = myEntityComponentSystem.CreateEntity("Test Entity.");
	Component* ca = myEntityComponentSystem.CreateComponent<TransformComponent>(e);
	myEntityComponentSystem.AddComponent(ca);
	myEntityComponentSystem.DestroyComponent(ca);

	Component* cb = myEntityComponentSystem.CreateComponent<TransformComponent>(e);
	myEntityComponentSystem.DestroyComponent(cb);

	Component* n = nullptr;
	myEntityComponentSystem.DestroyComponent(n);

	return;
}

void Engine::Terminate()
{
	myJobSystem.Terminate();
	myEntityComponentSystem.Terminate();
}