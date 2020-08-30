#include "Engine.h"
#include "Subsystem/Yellowstone/Yellowstone.h"

#include "Utility/Assert.h"

Engine::Engine()
	: myYellowstone(nullptr)
{
	myYellowstone = new Yellowstone();
}

Engine::~Engine()
{
}

bool Engine::Init()
{
	Assert(!myYellowstone->Initialize(), "Yellowstone Renderer FAILED to initialize! Cancelling init.");
	Assert(!myJobSystem.Init(), "Jobsystem FAILED to initialize! Cancelling init.");
	Assert(!myEntityComponentSystem.Init(), "Entity Component System FAILED to initialize! Cancelling init.");
	return true;
}

void Engine::Update()
{
	while (!myYellowstone->HasClosedWindow())
	{
		myYellowstone->Update();
	}
}

void Engine::Terminate()
{
	myYellowstone->Terminate();
	myJobSystem.Terminate();
	myEntityComponentSystem.Terminate();
}