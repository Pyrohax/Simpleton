#include "Engine.h"

#include <iostream>
#include <string>
#include <windows.h>

#undef AddJob

Engine::Engine(){}

Engine::~Engine(){}

auto job = []() -> bool
{
	DWORD i = 100;
	Sleep(i);

	return true;
};

bool Engine::Init()
{
	myJobSystem.Init();
	myEntityComponentSystem.Init();
	return false;
}

void Engine::Update()
{
	myJobSystem.AddJob(job);
	myJobSystem.AddJob(job);
	myJobSystem.AddJob(job);
	myJobSystem.AddJob(job);
	myJobSystem.AddJob(job);
	myJobSystem.AddJob(job);
	myJobSystem.AddJob(job);
	myJobSystem.AddJob(job);	
	myJobSystem.AddJob(job);
	myJobSystem.AddJob(job);
	myJobSystem.AddJob(job);
	myJobSystem.AddJob(job);
	myJobSystem.Terminate();

	myEntityComponentSystem.CreateEntity("New entity 1");
	myEntityComponentSystem.CreateEntity("New entity 2");
	myEntityComponentSystem.CreateEntity("New entity 3");
	myEntityComponentSystem.CreateEntity("New entity 4");
	myEntityComponentSystem.CreateEntity("New entity 5");
	myEntityComponentSystem.CreateEntity("New entity 6");
	myEntityComponentSystem.CreateEntity("New entity 7");
	myEntityComponentSystem.CreateEntity("New entity 8");
	myEntityComponentSystem.CreateEntity("New entity 9");


	myEntityComponentSystem.Update(0.016667);

	return;
}

void Engine::Terminate()
{
	myJobSystem.Terminate();
	myEntityComponentSystem.Terminate();
}