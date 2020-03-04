#pragma once
#include <thread>
#include <functional>
#include <vector>
#include <algorithm>
#include <future>


struct Job
{
private:
	static bool Idle()
	{
		return true;
	};
public:
	Job() : myThread(&Idle) {	}
	std::thread myThread;
	std::future<bool> myFuture;

};

class JobSystem
{
public:
	JobSystem();
	~JobSystem();

	bool Init();
	bool AddJob(std::function<bool()> f);

	bool CollectAllThreads();
	int CollectOneThread();
	unsigned int myThreadCount = 0;

private:
	std::vector<Job> myJobs;
};