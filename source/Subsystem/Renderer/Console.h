#pragma once

#include "imgui.h"
//#include "examples/imgui_impl_opengl3.h"
//#include "examples/imgui_impl_glfw.h"

#include <ctype.h>
#include <cstdlib>
#include <stdio.h>

struct Console
{
public:
    static Console& GetInstance()
    {
        static Console instance;
        return instance;
    }

    Console(Console const&) = delete;
    void operator=(Console const&) = delete;

    void ClearLog();
    void AddLog(const char* fmt, ...);
    void Draw(const char* title, bool* p_open);

private:
    Console();
    ~Console();

    void ExecCommand(const char* command_line);
    static int TextEditCallbackStub(ImGuiInputTextCallbackData* data);
    int TextEditCallback(ImGuiInputTextCallbackData* data);

    static void Strtrim(char* s) { char* str_end = s + strlen(s); while (str_end > s && str_end[-1] == ' ') str_end--; *str_end = 0; }

private:
    char myInputBuf[256];
    ImVector<char*> myItems;
    ImVector<const char*> myCommands;
    ImVector<char*> myHistory;
    int myHistoryPos;    // -1: new line, 0..History.Size-1 browsing history.
    ImGuiTextFilter myFilter;
    bool myAutoScroll;
    bool myScrollToBottom;
};
