#pragma once

#include <string>

namespace Log
{
	enum class Severity
	{
		Message,
		Error,
		Warning,
		Success
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

	static inline std::string GetSeverityAsString(Severity aSeverity)
	{
		switch (aSeverity)
		{
			case Log::Severity::Message:
				return "Message";
			case Log::Severity::Error:
				return "Error";
			case Log::Severity::Warning:
				return "Warning";
			case Log::Severity::Success:
				return "Success";
		}

		return "";
	}

	static inline std::string GetCategoryAsString(Category aCategory)
	{
		switch (aCategory)
		{
			case Log::Category::Assert:
				return "Assert";
			case Log::Category::Asset:
				return "Asset";
			case Log::Category::ECS:
				return "ECS";
			case Log::Category::Command:
				return "Command";
			case Log::Category::Rendering:
				return "Rendering";
			case Log::Category::Math:
				return "Math";
			case Log::Category::World:
				return "World";
			case Log::Category::Input:
				return "Input";
			case Log::Category::Time:
				return "Time";
			case Log::Category::Threading:
				return "Threading";
		}

		return "";
	}
}
