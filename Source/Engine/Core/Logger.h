#pragma once

#include "../Core/Log.h"

#include <vector>
#include <functional>

namespace Log
{
	class Logger
	{
	public:
		typedef std::function<void(Log::Package)> logCallback;
		static inline void SetCallback(logCallback&& aCallback)
		{
			myCallback = std::forward<logCallback>(aCallback);
			myHasCallback = true;
		}

		static void Print(Severity aSeverity, Category aCategory, const char* aFormat, ...);
		static const std::vector<Package>& GetLogs() { return myLogs; }

	private:
		static std::vector<Package> myLogs;
		static logCallback myCallback;
		static bool myHasCallback;
	};
}
