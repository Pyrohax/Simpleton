#include "JobSystem.h"

#include <chrono>

#include "../Core/Assert.h"
#include "../Core/Timer.h"

auto exampleJob = []() -> bool
{
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	return true;
};

JobSystem::JobSystem(){}

JobSystem::~JobSystem(){}

void JobSystem::Initialize()
{
	// Leave one thread open for the OS (common decency).
	myThreadCount = std::thread::hardware_concurrency() - 1;
	myJobs.reserve(myThreadCount);
	for (unsigned int i = 0; i < myThreadCount; ++i)
	{
		myJobs.emplace_back();
	}

	Assert(myThreadCount <= 0, "Hardware concurrency is invalid. Unsupported architecture?");
}

void JobSystem::Update(double aDeltaTime)
{
}

bool JobSystem::AddJob(const std::function<bool()> f)
{
	const int id = CollectOneThread();
	std::packaged_task<bool()> package(f);
	myJobs[id].myFuture = package.get_future();
	myJobs[id].myThread = std::thread(std::move(package));

	return true;
}

void JobSystem::Terminate()
{
	CollectAllThreads();
}

bool JobSystem::CollectAllThreads()
{
	for (Job& job : myJobs)
	{
		// If future is valid, so is the task.
		if (job.myFuture.valid())
		{
			job.myFuture.wait();
			if (job.myThread.joinable())
			{
				job.myThread.join();
				job = Job();
			}
		}
	}
	
	return true;
}

int JobSystem::CollectOneThread()
{
	// Wait for a thread to open up.
	const size_t jobCount = myJobs.size();
	const bool hasJobs = jobCount != 0;
	std::chrono::nanoseconds waitForThreadTime(1);

	Timer expireTimer;
	expireTimer.Start();

	while (hasJobs)
	{
		for (size_t i = 0; i < jobCount; ++i)
		{
			if (!myJobs[i].myFuture.valid())
			{
				return static_cast<int>(i);
			}
			if (myJobs[i].myFuture.wait_for(waitForThreadTime) == std::future_status::ready)
			{
				myJobs[i].myThread.join();
				return static_cast<int>(i);
			}
		}
		if (expireTimer.GetCurrentTime() > myMaximumExpirationTime)
		{
			expireTimer.Reset();
			Log::Print(LogType::WARNING, "Threads all being locked for a long time. If unintended, consider closing the engine");
		}
	}

	Assert(true, "Job count is zero! This should never happen!");

	return -1;
}
