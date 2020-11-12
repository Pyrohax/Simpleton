#pragma once

#include <algorithm>
#include <functional>
#include <future>
#include <thread>
#include <vector>

struct Job
{
public:
	std::thread myThread;
	std::future<bool> myFuture;

private:
	static bool Idle() { return true; }
};

class JobSystem
{
public:
	JobSystem();
	~JobSystem();

	void Initialize();
	void Update(double aDeltaTime);
	void Terminate();

	bool AddJob(const std::function<bool()> f);
	bool CollectAllThreads();

private:
	int CollectOneThread();

	std::vector<Job> myJobs;
	const float myMaximumExpirationTime = 3.f;
	unsigned int myThreadCount = 0;
};
