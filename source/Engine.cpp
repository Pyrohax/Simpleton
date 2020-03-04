#include "Engine.h"

#include <iostream>
#include <string>


Engine::Engine()
{
}

Engine::~Engine()
{
}

bool Engine::Init()
{
	js.Init();
	return false;
}

void Engine::Update()
{
	auto job = []() -> bool{
		for (int i = 0; i < 100; i++)
		{
			std::cout << "hello there!" << std::endl;
		}
		return true;
	};

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
	js.AddJob(job);
	js.AddJob(job);
	js.AddJob(job);
}

void Engine::Terminate()
{
}
