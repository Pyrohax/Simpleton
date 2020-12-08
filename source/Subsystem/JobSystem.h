#pragma once

#include <future>
#include <thread>
#include <vector>
#include <memory>

struct Job
{
	std::function<bool()> myFunction;
	std::thread** myThread;
	std::future<bool> myFuture;
};

class JobSystem
{
public:
	JobSystem();
	~JobSystem();

	bool Init();
	void Update(float aFrameTime);
	bool Terminate();

	void AddJob(const std::function<bool()> f);

private:
	void StartJob(Job& aJob, std::thread*& aThreadOut);
	void CollectFinishedThreads();

	std::vector<Job> myQueuedJobs;
	std::vector<Job> myRunningJobs;
	std::vector<std::thread*> myThreads;

	bool myNeedsUpdate;
};