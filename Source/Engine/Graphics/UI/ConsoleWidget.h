#pragma once

#include "Widget.h"
#include "../../Core/Logger.h"

#include <vector>

namespace UI
{
	class ImguiWrapper;

	class ConsoleWidget : public Widget
	{
	public:
		ConsoleWidget(ImguiWrapper* aWrapper, const std::string& aTitle);
		~ConsoleWidget();

		void Tick() override;

		void ClearLog();

		void ExecuteCommand(const char* aCommand);
		int TextEditCallback(ImGuiInputTextCallbackData* aData);

		static void Strtrim(char* s) { char* str_end = s + strlen(s); while (str_end > s && str_end[-1] == ' ') str_end--; *str_end = 0; }

	private:
		void AddLog(const char* aFormat, ...);
		void AddLogPackage(Log::Package aPackage);

	private:
		char myInputBuffer[256];
		std::vector<Log::Package> myItems;
		std::vector<const char*> myCommands;
		std::vector<char*> myHistory;
		std::string myTitle;
		int myHistoryPosition;    // -1: new line, 0..History.Size-1 browsing history.
		ImGuiTextFilter* myFilter;
		bool myAutoScroll;
		bool myScrollToBottom;
	};
}
