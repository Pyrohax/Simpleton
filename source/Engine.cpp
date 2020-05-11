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
	Entity* entity = myEntityComponentSystem.CreateEntity("Test Entity.");
	TransformComponent* component1 = myEntityComponentSystem.AddComponent<TransformComponent>(entity);
	myEntityComponentSystem.DestroyComponent<TransformComponent>(component1);

	Component* component2 = myEntityComponentSystem.AddComponent<Component>(entity);
	myEntityComponentSystem.DestroyComponent<Component>(component2);

	Component* component3 = myEntityComponentSystem.AddComponent<TransformComponent>(entity);
	myEntityComponentSystem.DestroyComponent<TransformComponent>(component1);

	return;
}

void Engine::Terminate()
{
	myJobSystem.Terminate();
	myEntityComponentSystem.Terminate();
}