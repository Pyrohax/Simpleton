#pragma once
#include <iostream>

static void Assert(bool aBehaviorIsFaulty, const char* aErrorMessage = "Undefined error.")
{
	if (aBehaviorIsFaulty)
	{
		std::cout << "\n" << aErrorMessage << "\n";
		abort();
	}
}