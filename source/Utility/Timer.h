#pragma once

#include "Logger.h"

#include <chrono>
#include <string>

class Timer
{
public:
	void Start()
	{
		myStartTime = std::chrono::high_resolution_clock::now();
	};

	float Stop()
	{
		myEndTime = std::chrono::high_resolution_clock::now();
		myDeltaTime = std::chrono::duration_cast<std::chrono::microseconds>(myEndTime - myStartTime).count() * 0.000001;
		return static_cast<float>(myDeltaTime);
	};

	double GetCurrentTime()
	{
		myDeltaTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - myStartTime).count() * 0.000001;
		return static_cast<double>(myDeltaTime);
	};

	void Print()
	{
		Log::Print(LogType::MESSAGE, "This took %s %s", std::to_string(GetCurrentTime()), " seconds");
	};

	void Reset()
	{
		myStartTime = std::chrono::high_resolution_clock::now();
	};

private:
	std::chrono::steady_clock::time_point myStartTime;
	std::chrono::steady_clock::time_point myEndTime;
	double myDeltaTime = 0.f;
};
