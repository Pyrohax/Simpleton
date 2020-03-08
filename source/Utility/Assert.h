#pragma once

#include "Logger.h"

static void Assert(bool aBehaviorIsFaulty, const char* aErrorMessage = "Undefined error.")
{
	if (aBehaviorIsFaulty)
	{
		Log::Print(aErrorMessage, LogType::PROBLEM);
		abort();
	}
}