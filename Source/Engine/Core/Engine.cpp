#include "Engine.h"

#include "../Core/ECS/EntityComponentSystem.h"
#include "../Graphics/Yellowstone.h"
#include "../World/World.h"
#include "DataManager.h"
#include "EngineContext.h"
#include "EngineSettings.h"

Engine::Engine()
	: myPreviousTime(0.0f)
	, myShouldShutdown(false)
{
	myContext = std::make_unique<EngineContext>();
	myDataManager = std::make_unique<DataManager>();
	myEntityComponentSystem = std::make_unique<EntityComponentSystem>();
	myWorld = std::make_unique<World>(myEntityComponentSystem.get());
}

Engine::~Engine()
{
	myWorld.reset();
	myEntityComponentSystem.reset();
	myDataManager.reset();
	myContext.reset();
}

void Engine::Initialize(BuildType aBuildType)
{
	myBuildType = aBuildType;

	myContext->RegisterSubsystem<Yellowstone>(TickType::Variable);

	myDataManager->ReadData();
	EngineSettings* settings = myDataManager->GetSerializableData<EngineSettings>();
	myVersion = settings->myVersion;

	myContext->Initialize();

	myEntityComponentSystem->Initialize();

	myWorld->Initialize();
	myWorld->LoadDefaultData();

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
