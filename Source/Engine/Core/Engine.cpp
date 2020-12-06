#include "Engine.h"

#include "Assert.h"
#include "EngineContext.h"
#include "../ECS/EntityComponentSystem.h"
#include "../Threading/JobSystem.h"
#include "../Graphics/Yellowstone.h"
#include "../World/World.h"

Engine::Engine()
	: myPreviousTime(0.0f)
	, myShouldShutdown(false)
{
	//AddSystem<EntityComponentSystem>();
	//AddSystem<JobSystem>();
	myWorld = new World();

	myContext = std::make_shared<EngineContext>();
	myContext->RegisterSubsystem<Yellowstone>(TickType::Variable);
}

Engine::~Engine()
{
}

void Engine::Initialize()
{
	myContext->Initialize();

	if (myWorld)
	{
		myWorld->LoadDummyData();
	}

	// TODO: improve architecture
	Yellowstone* yellowstone = myContext->GetSubsystem<Yellowstone>();
	yellowstone->CreateAssetBuffers();

	myPreviousTime = std::chrono::duration<float>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void Engine::Update()
{
	while (!GetShouldShutdown())
	{
		float currentTime = std::chrono::duration<float>(std::chrono::system_clock::now().time_since_epoch()).count();
		float frameTime = currentTime - myPreviousTime;
		myPreviousTime = currentTime;

		// TODO: fix timer and use corresponding deltatime
		myContext->Tick(TickType::Variable, 0.0167f);
		myContext->Tick(TickType::Smooth, 0.0167f);
	}
}

void Engine::Terminate()
{
	myWorld->Destroy();
	delete myWorld;
}
