#pragma once

class Renderer;
class JobSystem;
class EntityComponentSystem;

class Engine
{
public:
	Engine();
	~Engine();

	bool Init();
	void Update();
	void Terminate();

	JobSystem* myJobSystem;
	EntityComponentSystem* myEntityComponentSystem;

private:
	Renderer* myRenderer;
	double myPreviousTime;
};
