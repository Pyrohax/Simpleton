#pragma once

#include "Logger.h"

#include <exception>

static void Assert(bool aBehaviorIsFaulty, const char* aFormat, ...)
{
	if (aBehaviorIsFaulty)
	{
		va_list argumentLeft, argumentRight;
		va_start(argumentLeft, aFormat);
		va_copy(argumentRight, argumentLeft);
		int size = _vscprintf(aFormat, argumentRight) + 1;
		va_end(argumentRight);

		char* buffer = new char[size];
		vsnprintf(buffer, size, aFormat, argumentLeft);
		va_end(argumentLeft);

		Log::Print(LogType::PROBLEM, buffer);

#ifdef NDEBUG
		abort();
#else
		throw std::runtime_error(buffer);
#endif
	}
}
