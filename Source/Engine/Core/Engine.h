#pragma once

#include <memory>
#include <vector>

class EngineContext;
class World;

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
	void Terminate();

	void SetShouldShutdown(bool aShouldShutdown) { myShouldShutdown = aShouldShutdown; }
	constexpr bool GetShouldShutdown() { return myShouldShutdown; }

	World* GetWorld() const { return myWorld; }
	auto GetContext() const { return myContext.get(); }
	const BuildType GetBuildType() const { return myBuildType; }

private:
	Engine();
	~Engine();

private:
	std::shared_ptr<EngineContext> myContext;
	World* myWorld;
	BuildType myBuildType;
	float myPreviousTime;
	bool myShouldShutdown;
};
