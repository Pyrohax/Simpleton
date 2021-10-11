#include "JobSystem.h"

#include <algorithm>
#include <chrono>
#include <functional>

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
	const int myThreadCount = std::thread::hardware_concurrency() - 1;
	Assert(myThreadCount <= 0, "Hardware concurrency is invalid. Unsupported architecture?");
}

void JobSystem::Update(double aDeltaTime)
{
}

JobSystem::~JobSystem(){}

//// Example for adding jobs:
//auto exampleJob = []() -> bool
//{
//	std::this_thread::sleep_for(std::chrono::milliseconds(100));
//	return true;
//};

bool JobSystem::Init()
{
	//// Example for adding jobs:
	//for (int i = 0; i < 30000; i++)
	//	AddJob(exampleJob);

	return true;
}

void JobSystem::Update(float aFrameTime)
{
	CollectFinishedThreads();

	// Add jobs to the queue.
	if (myNeedsUpdate && !myQueuedJobs.empty())
	{
		// Any threads not in use?
		std::vector<std::thread**> emptyThreads;
		int emptyThreadCount = 0;
		for (int threadIndex = 0; threadIndex <= myThreads.capacity() - 1 && emptyThreadCount <= myQueuedJobs.size() - 1; ++threadIndex)
		{
			if (myThreads[threadIndex] == nullptr)
			{
				emptyThreads.push_back(&myThreads[threadIndex]);
				emptyThreadCount++;
			}
		}

		// Put all available jobs in there.
		for (int i = emptyThreads.size() - 1; i >= 0 && emptyThreadCount > 0; --i)
		{
			Job& job = myQueuedJobs[myQueuedJobs.size() - i - 1];
			StartJob(job, *emptyThreads[i]);
			myQueuedJobs.erase(myQueuedJobs.end() - i - 1);
			emptyThreadCount--;
		}
	}

	myNeedsUpdate = false;
	return;
}

bool JobSystem::Terminate()
{
	while (!myRunningJobs.empty())
		CollectFinishedThreads();

	return true;
}

void JobSystem::AddJob(const std::function<bool()> aFunction)
{
	myQueuedJobs.push_back(Job{ aFunction, nullptr, std::future<bool>() });
	myNeedsUpdate = true;
}

void JobSystem::StartJob(Job& aJob, std::thread*& aThreadOut)
{
	std::packaged_task<bool()> package(aJob.myFunction);
	myRunningJobs.emplace_back(Job{aJob.myFunction, &aThreadOut, package.get_future()});
	aThreadOut = new std::thread(std::move(package));
	return;
}

void JobSystem::CollectFinishedThreads()
{
	for (int i = myRunningJobs.size() - 1; i >= 0; --i)
	{
		Job& job = myRunningJobs[i];
		const std::future_status status = job.myFuture.wait_for(std::chrono::seconds(0));
		if (status == std::future_status::ready)
		{
			Log::Print(LogType::MESSAGE, "A task finished with result %i!", job.myFuture.get());

			for (int i = 0; i < myThreads.size(); ++i)
			{
				std::thread* threadToRemove = myThreads[i];
				if (threadToRemove == *job.myThread)
				{
					threadToRemove->join();
					delete(threadToRemove);
					myThreads[i] = nullptr;
					break;
				}
			}
		}
		if (expireTimer.GetCurrentTime() > myMaximumExpirationTime)
		{
			expireTimer.Reset();
			Log::Logger::Print(Log::Severity::Warning, Log::Category::Threading, "Threads all being locked for a long time. If unintended, consider closing the engine");
		}
	}

	Assert(true, "Job count is zero! This should never happen!");

	return -1;
}
