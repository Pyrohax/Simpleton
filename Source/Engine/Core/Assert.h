#pragma once

#include "Logger.h"

#include <stdexcept>
#include <cstdarg>

static inline void Assert(bool aBehaviorIsFaulty, const char* aFormat, ...)
{
	if (!aBehaviorIsFaulty)
		return;

	va_list argumentLeft, argumentRight;
	va_start(argumentLeft, aFormat);
	va_copy(argumentRight, argumentLeft);
	int size = _vscprintf(aFormat, argumentRight) + 1;
	va_end(argumentRight);

	char* buffer = new char[size];
	vsnprintf(buffer, size, aFormat, argumentLeft);
	va_end(argumentLeft);

	Log::Logger::Print(Log::Severity::Error, Log::Category::Assert, buffer);

#ifdef NDEBUG
	abort();
#else
	throw std::runtime_error(buffer);
#endif
}
