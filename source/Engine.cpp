#include "Engine.h"

#include "Utility/Assert.h"

Engine::Engine()
	: myEntityComponentSystem(this)
{
}

Engine::~Engine()
{
}

bool Engine::Init()
{
	Assert(!myYellowstone.Init(), "Yellowstone Renderer FAILED to initialize! Cancelling init.");
	Assert(!myJobSystem.Init(), "Jobsystem FAILED to initialize! Cancelling init.");
	Assert(!myEntityComponentSystem.Init(), "Entity Component System FAILED to initialize! Cancelling init.");
	return true;
}

void Engine::Update()
{
	while (!myYellowstone.HasClosedWindow())
	{
		myYellowstone.PollEvents();
	}
}

void Engine::Terminate()
{
	myYellowstone.Terminate();
	myJobSystem.Terminate();
	myEntityComponentSystem.Terminate();
}