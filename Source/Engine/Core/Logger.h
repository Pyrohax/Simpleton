#pragma once

#include "../Graphics/OpenGL/ConsoleO.h"

#include <fstream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <cstdarg>

// 4 types of loggables, a problem, a success, a warning or a message.
enum class LogType
{
	PROBLEM = 1 << 1,
	SUCCESS = 1 << 2,
	WARNING = 1 << 3,
	MESSAGE = 1 << 4
};

enum class DateTimeFormat
{
	DateTime,
	Date,
	Time
};

static inline const std::string GetCurrentDateTime(DateTimeFormat aFormat)
{
	time_t now = time(0);
	struct tm timeStruct;
	char buffer[12] = "";
	localtime_s(&timeStruct, &now);

	const char* timeFormat;
	switch (aFormat)
	{
		case DateTimeFormat::Date:
			timeFormat = "%Y-%m-%d";
			break;
		case DateTimeFormat::Time:
			timeFormat = "%X";
			break;
		case DateTimeFormat::DateTime:
		default:
			timeFormat = "%Y-%m-%d %X";
			break;
	}

	strftime(buffer, sizeof(buffer), timeFormat, &timeStruct);
	std::string result(buffer);
	return result;
};

// Logger prints anything text based based on it's LogType and on the LogDebugLevel.
struct Log
{
public:
	// The log level defines what is printed and what isn't.
#define DebugLoggingTypes (										\
  static_cast<unsigned char>(LogType::PROBLEM)					\
| static_cast<unsigned char>(LogType::SUCCESS)					\
| static_cast<unsigned char>(LogType::WARNING)					\
| static_cast<unsigned char>(LogType::MESSAGE)					)			

	static inline void Print(const LogType aType, const char* aFormat, ...)
	{
		std::string prefix = "";
		switch (aType)
		{
			case LogType::PROBLEM:
				prefix = "(P)";
				break;
			case LogType::SUCCESS:
				prefix = "(S)";
				break;
			case LogType::WARNING:
				prefix = "(W)";
				break;
			case LogType::MESSAGE:
				prefix = "(M)";
				break;
			default:
				break;
		}

		bool shouldPrint = static_cast<char>(aType) & static_cast<char>(DebugLoggingTypes);
		if (shouldPrint || DebugLoggingTypes == 0)
		{
			va_list argumentLeft, argumentRight;
			va_start(argumentLeft, aFormat);
			va_copy(argumentRight, argumentLeft);
			int size = _vscprintf(aFormat, argumentRight) + 1;
			va_end(argumentRight);

			char* buffer = new char[size];
			vsnprintf(buffer, size, aFormat, argumentLeft);
			va_end(argumentLeft);

			std::string time = GetCurrentDateTime(DateTimeFormat::Time);
			std::string log(prefix + " " + time + " " + buffer);
			ConsoleO::GetInstance().AddLog(log.c_str());

			std::string filePath = GetCurrentDateTime(DateTimeFormat::Date) + ".txt";
			std::ofstream outstream(filePath.c_str(), std::ios_base::out | std::ios_base::app);
			outstream << time << '\t' << buffer << '\n';
			outstream.close();
		}
	};
#undef LogDebugLevel
};
