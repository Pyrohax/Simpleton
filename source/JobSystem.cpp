#include "JobSystem.h"

JobSystem::JobSystem(){}

JobSystem::~JobSystem(){}

bool JobSystem::Init()
{
	myThreadCount = std::thread::hardware_concurrency() - 1;
	myJobs.reserve(myThreadCount);
	for (unsigned int i = 0; i < myThreadCount; ++i)
	{
		myJobs.emplace_back();
	}

	CollectAllThreads();
	return true;
}

bool JobSystem::AddJob(std::function<bool()> f)
{
	int id = CollectOneThread();
	std::packaged_task<bool()> package(f);
	myJobs[id].myFuture = package.get_future();
	myJobs[id].myThread = std::thread(std::move(package));

	return true;
}

bool JobSystem::CollectAllThreads()
{
	for (unsigned int i = 0; i < myJobs.size(); ++i)
	{
		// If future is valid, so is the task.
		if (myJobs[i].myFuture.valid() && myJobs[i].myThread.joinable())
		{
			myJobs[i].myFuture.wait();
		}
		myJobs[i].myThread.join();
	}
	return true;
}

int JobSystem::CollectOneThread()
{
	std::chrono::milliseconds sec(1);
	// Wait for a thread to open up.
	while (true)
	{
		for (size_t i = 0; i < myJobs.capacity(); ++i)
		{
			if (!myJobs[i].myFuture.valid())
			{
				return static_cast<int>(i);
			}
			if (myJobs[i].myFuture.wait_for(sec) == std::future_status::ready)
			{
				myJobs[i].myThread.join();
				return static_cast<int>(i);
			}
		}
	}
}