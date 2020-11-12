#include "Engine.h"

#include "Core/Assert.h"
#include "System/EntityComponentSystem.h"
#include "System/JobSystem.h"
#include "System/OpenGLRenderer.h"
#include "World/World.h"

Engine::Engine()
	: myPreviousTime(0.0f)
	, myShouldShutdown(false)
{
	//AddSystem<EntityComponentSystem>();
	//AddSystem<JobSystem>();
	myWorld = new World();
	myRenderer = new OpenGLRenderer();
}

Engine::~Engine()
{
}

void Engine::Init()
{
	if (myRenderer)
	{
		myRenderer->Initialize();
	}

	if (myWorld)
	{
		myWorld->LoadDummyData();
	}

	OpenGLRenderer* renderer = dynamic_cast<OpenGLRenderer*>(myRenderer);
	renderer->CreateAssetBuffers();

	myPreviousTime = std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void Engine::Update()
{
	while (!GetShouldShutdown())
	{
		double currentTime = std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch()).count();
		double frameTime = currentTime - myPreviousTime;
		myPreviousTime = currentTime;

		if (myRenderer)
		{
			OpenGLRenderer* renderer = dynamic_cast<OpenGLRenderer*>(myRenderer);
			renderer->Update(frameTime);
			myShouldShutdown = renderer->HasClosedWindow();
		}
	}
}

void Engine::Terminate()
{
	myRenderer->Terminate();
	myWorld->Destroy();
	// TODO: Terminate systems
}
