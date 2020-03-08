#pragma once

#include <string>
#include <iostream>

// 4 types of loggables, a problem, a success, a warning or a message.
enum class LogType
{
	PROBLEM = 1 << 1,
	SUCCESS = 1 << 2,
	WARNING = 1 << 3,
	MESSAGE = 1 << 4 
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

	template <typename T>
	static void Print(T log, const LogType type = LogType::MESSAGE)
	{
		// Checks if the input element is printable for std::cout.
		static_assert(
			std::is_arithmetic<T>::value
			|| std::is_base_of<std::string, T>::value
			|| std::is_same<const char*, T>::value, "Printed Element needs to be either a number, a string, or a character.");

		if (((static_cast<char>(LogType::PROBLEM) & static_cast<char>(type)) & static_cast<char>(DebugLoggingTypes)) || DebugLoggingTypes == 0) std::cout << "(X)";													  		 
		if (((static_cast<char>(LogType::SUCCESS) & static_cast<char>(type)) & static_cast<char>(DebugLoggingTypes)) || DebugLoggingTypes == 0) std::cout << "(V)";							  						  		  
		if (((static_cast<char>(LogType::WARNING) & static_cast<char>(type)) & static_cast<char>(DebugLoggingTypes)) || DebugLoggingTypes == 0) std::cout << "(!)";							  								    
 		if (((static_cast<char>(LogType::MESSAGE) & static_cast<char>(type)) & static_cast<char>(DebugLoggingTypes)) || DebugLoggingTypes == 0) std::cout << "( )";

		bool shouldPrint = static_cast<char>(type) & static_cast<char>(DebugLoggingTypes);
		if (shouldPrint || DebugLoggingTypes == 0)
		{
			std::cout << " " << log << "\n";
		}
	};
#undef LogDebugLevel
};