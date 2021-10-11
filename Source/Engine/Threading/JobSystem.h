#pragma once

#include <future>
#include <thread>
#include <vector>
#include <memory>

struct Job
{
	std::thread** myThread;
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
	void StartJob(Job& aJob, std::thread*& aThreadOut);
	void CollectFinishedThreads();

	std::vector<Job> myQueuedJobs;
	std::vector<Job> myRunningJobs;
	std::vector<std::thread*> myThreads;

	std::vector<Job> myJobs;
	const float myMaximumExpirationTime = 3.f;
	unsigned int myThreadCount = 0;
};
