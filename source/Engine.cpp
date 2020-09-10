#include "Engine.h"
#include "Subsystem/Renderer/Renderer.h"

#include "Utility/Assert.h"

Engine::Engine()
	: myRenderer(nullptr)
{
	myRenderer = new Renderer();
}

Engine::~Engine()
{
}

bool Engine::Init()
{
	Assert(!myRenderer->Initialize(), "Renderer FAILED to initialize! Cancelling init.");
	Assert(!myJobSystem.Init(), "Jobsystem FAILED to initialize! Cancelling init.");
	Assert(!myEntityComponentSystem.Init(), "Entity Component System FAILED to initialize! Cancelling init.");
	return true;
}

void Engine::Update()
{
	while (!myRenderer->HasClosedWindow())
	{
		myRenderer->Update();
	}
}

void Engine::Terminate()
{
	myRenderer->Terminate();
	myJobSystem.Terminate();
	myEntityComponentSystem.Terminate();
}