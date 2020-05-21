#include "Engine.h"

Engine::Engine()
	: myEntityComponentSystem(this)
{
}

Engine::~Engine()
{
}

bool Engine::Init()
{
	myYellowstone.Init();
	if (myJobSystem.Init() && myEntityComponentSystem.Init())
		return true;
	else
		return false;
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