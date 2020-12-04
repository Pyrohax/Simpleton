#include "Engine.h"
#include "Subsystem/Renderer/Renderer.h"

#include "Utility/Assert.h"


Engine::Engine()
	: myRenderer(nullptr)
	, myPreviousTime(0.0f)
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

	myPreviousTime = std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count();

	return true;
}

void Engine::Update()
{
	while (!myRenderer->HasClosedWindow())
	{
		double currentTime = std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count();
		double frameTime = currentTime - myPreviousTime;
		myPreviousTime = currentTime;

		myJobSystem.Update(frameTime);
		myRenderer->Update(frameTime);
	}
}

void Engine::Terminate()
{
	myRenderer->Terminate();
	myJobSystem.Terminate();
	myEntityComponentSystem.Terminate();
}