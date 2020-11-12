#pragma once

class World;
class Renderer;

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

	void Init();
	void Update();
	void Terminate();

	void SetShouldShutdown(bool aShouldShutdown) { myShouldShutdown = aShouldShutdown; }
	constexpr bool GetShouldShutdown() { return myShouldShutdown; }

	World* GetWorld() const { return myWorld; }

private:
	Engine();
	~Engine();

private:
	World* myWorld;
	Renderer* myRenderer;
	double myPreviousTime;
	bool myShouldShutdown;
};
