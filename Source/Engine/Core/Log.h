#pragma once

#include <string>

namespace Log
{
	enum class Severity
	{
		Message,
		Error,
		Warning,
		Succes
	};

	enum class Category
	{
		Assert,
		Asset,
		ECS,
		Command,
		Rendering,
		Math,
		World,
		Input,
		Time,
		Threading
	};

	struct Package
	{
		Severity mySeverity;
		Category myCategory;
		std::string myTimestamp;
		std::string myMessage;
	};
}
