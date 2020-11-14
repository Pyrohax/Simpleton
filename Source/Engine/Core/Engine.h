#pragma once

#include <memory>
#include <vector>

class EngineContext;
class World;

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

	void Initialize();
	void Update();
	void Terminate();

	void SetShouldShutdown(bool aShouldShutdown) { myShouldShutdown = aShouldShutdown; }
	constexpr bool GetShouldShutdown() { return myShouldShutdown; }

	World* GetWorld() const { return myWorld; }
	auto GetContext() const { return myContext.get(); }

private:
	Engine();
	~Engine();

private:
	std::shared_ptr<EngineContext> myContext;
	World* myWorld;
	float myPreviousTime;
	bool myShouldShutdown;
};
