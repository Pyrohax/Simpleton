#pragma once

#include <ctype.h>
#include <cstdlib>
#include <stdio.h>
#include <vector>

struct ImGuiInputTextCallbackData;
struct ImGuiTextFilter;

struct ConsoleO
{
public:
    static ConsoleO& GetInstance()
    {
        static ConsoleO instance;
        return instance;
    }

    ConsoleO(ConsoleO const&) = delete;
    void operator=(ConsoleO const&) = delete;

    void ClearLog();
    void AddLog(const char* aFormat, ...);
    void Draw(const char* aTitle);

private:
    ConsoleO();
    ~ConsoleO();

    void ExecuteCommand(const char* aCommand);
    int TextEditCallback(ImGuiInputTextCallbackData* aData);

    static void Strtrim(char* s) { char* str_end = s + strlen(s); while (str_end > s && str_end[-1] == ' ') str_end--; *str_end = 0; }

private:
    char myInputBuffer[256];
    std::vector<char*> myItems;
    std::vector<const char*> myCommands;
    std::vector<char*> myHistory;
    int myHistoryPosition;    // -1: new line, 0..History.Size-1 browsing history.
    ImGuiTextFilter* myFilter;
    bool myAutoScroll;
    bool myScrollToBottom;
};
