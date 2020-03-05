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
	js.Init();
	return false;
}

void Engine::Update()
{
	js.AddJob(job);
	js.AddJob(job);
	js.AddJob(job);
	js.AddJob(job);
	js.AddJob(job);
	js.AddJob(job);
	js.AddJob(job);
	js.AddJob(job);	
	js.AddJob(job);
	js.AddJob(job);
	js.AddJob(job);
	js.AddJob(job);
	js.Terminate();

	return;
}

void Engine::Terminate()
{
	js.Terminate();
}
