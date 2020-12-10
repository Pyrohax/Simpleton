#include "Logger.h"

#include "../Core/Time.h"

#include <stdio.h>
#include <cstdarg>
#include <fstream>
#include <vector>

std::vector<Log::Package> Log::Logger::myLogs;
Log::Logger::logCallback Log::Logger::myCallback;
bool Log::Logger::myHasCallback = false;

void Log::Logger::Print(Severity aSeverity, Category aCategory, const char* aFormat, ...)
{
	va_list argumentLeft, argumentRight;
	va_start(argumentLeft, aFormat);
	va_copy(argumentRight, argumentLeft);
	int size = _vscprintf(aFormat, argumentRight) + 1;
	va_end(argumentRight);

	char* buffer = new char[size];
	vsnprintf(buffer, size, aFormat, argumentLeft);
	va_end(argumentLeft);

	const std::string time = Time::GetCurrentTime();

	Package package;
	package.mySeverity = aSeverity;
	package.myCategory = aCategory;
	package.myTimestamp = time;
	package.myMessage = buffer;

	myLogs.emplace_back(package);
	
	if (myHasCallback)
		myCallback(package);

	std::string filePath = Time::GetCurrentDate() + ".txt";
	std::ofstream outstream(filePath.c_str(), std::ios_base::out | std::ios_base::app);
	outstream << time << '\t' << buffer << '\n';
	outstream.close();
}
