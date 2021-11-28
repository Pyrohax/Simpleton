#pragma once

#include <memory>
#include <vector>
#include <string>

class DataManager;
class EngineContext;
class World;
class EntityComponentSystem;

enum class BuildType
{
	Headless,
	Editor,
	Game
};

class Engine
{
public:
	static Engine& GetInstance()
	{
		static Engine instance;
		return instance;
	}

	Engine(Engine const&) = delete;
	void operator=(Engine const&) = delete;

	void Initialize(BuildType aBuildType);
	void Update();
	void Shutdown();

	void SetShouldShutdown(bool aShouldShutdown) { myShouldShutdown = aShouldShutdown; }
	constexpr bool GetShouldShutdown() { return myShouldShutdown; }

	World& GetWorld() const { return *myWorld.get(); }
	EntityComponentSystem& GetEntityComponentSystem() const { return *myEntityComponentSystem.get(); }
	EngineContext& GetContext() const { return *myContext.get(); }
	const BuildType GetBuildType() const { return myBuildType; }
	const std::string& GetVersion() const { return myVersion; }

private:
	Engine();
	~Engine();

private:
	std::unique_ptr<EngineContext> myContext;
	std::unique_ptr<DataManager> myDataManager;
	std::unique_ptr<EntityComponentSystem> myEntityComponentSystem;
	std::unique_ptr<World> myWorld;
	std::string myVersion;
	BuildType myBuildType;
	float myPreviousTime;
	bool myShouldShutdown;
};
