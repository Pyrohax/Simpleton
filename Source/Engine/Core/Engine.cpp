#include "Engine.h"

#include "../Graphics/Yellowstone.h"
#include "../Threading/JobSystem.h"
#include "../World/World.h"
#include "Assert.h"
#include "DataManager.h"
#include "EngineContext.h"
#include "EngineSettings.h"

Engine::Engine()
	: myPreviousTime(0.0f)
	, myShouldShutdown(false)
{
	myDataManager = new DataManager();
	myWorld = new World();

	myContext = std::make_shared<EngineContext>();
	myContext->RegisterSubsystem<Yellowstone>(TickType::Variable);
}

Engine::~Engine()
{
}

void Engine::Initialize(BuildType aBuildType)
{
	myBuildType = aBuildType;

	myDataManager->ReadData();
	EngineSettings* settings = myDataManager->GetSerializableData<EngineSettings>();
	myVersion = settings->myVersion;

	myContext->Initialize();

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
