#pragma once

#include "Logger.h"

template <typename T>
static void Assert(bool aBehaviorIsFaulty, T aErrorMessage = "Undefined error.")
{
	if (aBehaviorIsFaulty)
	{
		Log::Print(aErrorMessage, LogType::PROBLEM);
#ifdef NDEBUG
		abort();
#endif
	}
}