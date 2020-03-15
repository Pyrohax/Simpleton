#include "Engine.h"
#include "Renderer/Yellowstone.h"

#include <windows.h>

#undef AddJob

Engine::Engine()
	: myEntityComponentSystem(this)
	, myYellowstone(nullptr)
{
}

Engine::~Engine()
{
}

auto exampleJob = []() -> bool
{
	Sleep(100);

	return true;
};

bool Engine::Init()
{
	myYellowstone = new Yellowstone();
	myYellowstone->CreatePlateau();
	myYellowstone->CheckExtensions();

	myJobSystem.Init();
	myEntityComponentSystem.Init();
	return false;
}

void Engine::Update()
{
	while (!glfwWindowShouldClose(myYellowstone->GetWindow()))
	{
		glfwPollEvents();
	}
	// Leaving this in to show as a good example.
	/*Entity* e = myEntityComponentSystem.CreateEntity("Test Entity.");
	Component* ca = myEntityComponentSystem.CreateComponent<TransformComponent>(e);
	myEntityComponentSystem.AddComponent(ca);
	myEntityComponentSystem.DestroyComponent(ca);

	Component* cb = myEntityComponentSystem.CreateComponent<TransformComponent>(e);
	myEntityComponentSystem.DestroyComponent(cb);

	Component* n = nullptr;
	myEntityComponentSystem.DestroyComponent(n);*/
}

void Engine::Terminate()
{
	myYellowstone->Shutdown();
	myJobSystem.Terminate();
	myEntityComponentSystem.Terminate();
}