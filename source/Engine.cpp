#include "Engine.h"

#include <iostream>
#include <string>
#include <windows.h>

#undef AddJob

Engine::Engine(){}

Engine::~Engine(){}

auto job = []() -> bool
{
	DWORD i = 10000;
	Sleep(i);

	return true;
};

bool Engine::Init()
{
	myJobSystem.Init();
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

	return;
}

void Engine::Terminate()
{
	myJobSystem.Terminate();
}