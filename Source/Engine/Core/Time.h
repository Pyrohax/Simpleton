#pragma once

#include <string>
#include <time.h>

namespace Time
{
	static inline const std::string GetCurrentDate()
	{
		time_t now = time(0);
		struct tm timeStruct;
		char buffer[12] = "";
		localtime_s(&timeStruct, &now);

		strftime(buffer, sizeof(buffer), "%Y-%m-%d", &timeStruct);
		std::string result(buffer);

		return result;
	};

	static inline const std::string GetCurrentTime()
	{
		time_t now = time(0);
		struct tm timeStruct;
		char buffer[12] = "";
		localtime_s(&timeStruct, &now);

		strftime(buffer, sizeof(buffer), "%H:%M:%S", &timeStruct);
		std::string result(buffer);

		return result;
	};

	static inline const std::string GetCurrentDateTime()
	{
		time_t now = time(0);
		struct tm timeStruct;
		char bufferDate[12] = "";
		char bufferTime[12] = "";
		localtime_s(&timeStruct, &now);

		strftime(bufferDate, sizeof(bufferDate), "%Y-%m-%d", &timeStruct);
		strftime(bufferTime, sizeof(bufferTime), "%X", &timeStruct);
		std::string result(bufferDate);
		result.append(" ");
		result.append(bufferTime);

		return result;
	};
}
