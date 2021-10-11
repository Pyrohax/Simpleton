#include "ConsoleWidget.h"

#include "ImguiWrapper.h"
#include "../../Core/Time.h"

UI::ConsoleWidget::ConsoleWidget(ImguiWrapper* aWrapper, const std::string& aTitle)
    : Widget(aWrapper, aTitle)
    , myTitle(aTitle)
{
    ClearLog();
    memset(myInputBuffer, 0, sizeof(myInputBuffer));
    myHistoryPosition = -1;
    myFilter = new ImGuiTextFilter();

    Log::Logger::SetCallback([this](const Log::Package& aPackage) { AddLogPackage(aPackage); });

    const std::vector<Log::Package>& logs = Log::Logger::GetLogs();
    for (auto& log : logs)
    {
        AddLogPackage(log);
    }

    // "CLASSIFY" is here to provide the test case where "C"+[tab] completes to "CL" and display multiple matches.
    myCommands.push_back("HELP");
    myCommands.push_back("HISTORY");
    myCommands.push_back("CLEAR");
    myCommands.push_back("CLASSIFY");
    myAutoScroll = true;
    myScrollToBottom = false;
}

UI::ConsoleWidget::~ConsoleWidget()
{
    ClearLog();

    for (int i = 0; i < myHistory.size(); i++)
    {
        free(myHistory[i]);
    }

    delete myFilter;
}

void UI::ConsoleWidget::Tick()
{
    ImGui::SetNextWindowSize(ImVec2(520.0f, 600.0f), ImGuiCond_FirstUseEver);

    static ImGuiTableFlags tableFlags = ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_NoPadOuterX | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY;
    static ImGuiTableColumnFlags columnFlags = ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoSort;
    static ImGuiTableRowFlags rowFlags = ImGuiTableRowFlags_None;
    const char* column_names[4] = { "Time", "Severity", "Category", "Message" };
    if (ImGui::BeginTable("##Logs", 4, tableFlags))
    {
        ImGui::TableSetupColumn(column_names[0], columnFlags);
        ImGui::TableSetupColumn(column_names[1], columnFlags);
        ImGui::TableSetupColumn(column_names[2], columnFlags);
        ImGui::TableSetupColumn(column_names[3], columnFlags);
        ImGui::TableHeadersRow();

        for (auto& item : myItems)
        {
            ImVec4 color;
            switch (item.mySeverity)
            {
                case Log::Severity::Error:
                    color = ImVec4(1.0f, 0.4f, 0.4f, 1.0f);
                    break;
                case Log::Severity::Message:
                    color = ImVec4(1.0f, 0.8f, 0.6f, 1.0f);
                    break;
                case Log::Severity::Success:
                    color = ImVec4(0.4f, 1.0f, 0.4f, 1.0f);
                    break;
                case Log::Severity::Warning:
                    color = ImVec4(0.9f, 0.9f, 0.1f, 1.0f);
                    break;
            }

            ImGui::TableNextRow(rowFlags);
            ImGui::TableNextColumn();
            ImGui::Text("%s", item.myTimestamp.c_str());

            ImGui::TableNextColumn();
            ImGui::PushStyleColor(ImGuiCol_Text, color);
            ImGui::Text("%s", Log::GetSeverityAsString(item.mySeverity).c_str());
            ImGui::PopStyleColor();

            ImGui::TableNextColumn();
            ImGui::Text("%s", Log::GetCategoryAsString(item.myCategory).c_str());

            ImGui::TableNextColumn();
            ImGui::Text("%s", item.myMessage.c_str());
        }

        ImGui::EndTable();
    }

    // Command-line
    bool reclaim_focus = false;
    ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;

    auto textEditCallback = [](ImGuiInputTextCallbackData* aData)
    {
        UI::ConsoleWidget* console = (UI::ConsoleWidget*)aData->UserData;
        return console->TextEditCallback(aData);
    };

    if (ImGui::InputText("Command", myInputBuffer, IM_ARRAYSIZE(myInputBuffer), input_text_flags, textEditCallback, (void*)this))
    {
        char* inputBuffer = myInputBuffer;
        Strtrim(inputBuffer);

        if (inputBuffer[0])
            ExecuteCommand(inputBuffer);

        strcpy_s(inputBuffer, sizeof(inputBuffer), "");
        reclaim_focus = true;
    }

    // Auto-focus on window apparition
    ImGui::SetItemDefaultFocus();
    if (reclaim_focus)
        ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget
}

void UI::ConsoleWidget::ExecuteCommand(const char* aCommand)
{
    AddLog("# %s\n", aCommand);

    // Insert into history. First find match and delete it so it can be pushed to the back.
    // This isn't trying to be smart or optimal.
    myHistoryPosition = -1;
    int historySize = static_cast<int>(myHistory.size());
    for (int i = historySize - 1; i >= 0; i--)
        if (strcmp(myHistory[i], aCommand) == 0)
        {
            free(myHistory[i]);
            myHistory.erase(myHistory.begin() + i);
            break;
        }
    myHistory.push_back(_strdup(aCommand));

    // Process command
    if (strcmp(aCommand, "CLEAR") == 0)
    {
        ClearLog();
    }
    else if (strcmp(aCommand, "HELP") == 0)
    {
        AddLog("Commands:");
        for (int i = 0; i < myCommands.size(); i++)
            AddLog("- %s", myCommands[i]);
    }
    else if (strcmp(aCommand, "HISTORY") == 0)
    {
        int first = historySize - 10;
        for (int i = first > 0 ? first : 0; i < myHistory.size(); i++)
            AddLog("%3d: %s\n", i, myHistory[i]);
    }
    else
    {
        AddLog("Unknown command: '%s'\n", aCommand);
    }

    // On command input, we scroll to bottom even if AutoScroll==false
    myScrollToBottom = true;
}

void UI::ConsoleWidget::ClearLog()
{
    myItems.clear();
}

void UI::ConsoleWidget::AddLog(const char* aFormat, ...)
{
    va_list argumentLeft, argumentRight;
    va_start(argumentLeft, aFormat);
    va_copy(argumentRight, argumentLeft);
    int size = _vscprintf(aFormat, argumentRight) + 1;
    va_end(argumentRight);

    char* buffer = new char[size];
    vsnprintf(buffer, size, aFormat, argumentLeft);
    va_end(argumentLeft);

    Log::Package package;
    package.myCategory = Log::Category::Command;
    package.mySeverity = Log::Severity::Message;
    package.myTimestamp = Time::GetCurrentTime();
    package.myMessage = buffer;

    myItems.push_back(package);
}

void UI::ConsoleWidget::AddLogPackage(Log::Package aPackage)
{
    myItems.push_back(aPackage);
}

int UI::ConsoleWidget::TextEditCallback(ImGuiInputTextCallbackData* aData)
{
    //AddLog("cursor: %d, selection: %d-%d", data->CursorPos, data->SelectionStart, data->SelectionEnd);
    switch (aData->EventFlag)
    {
        case ImGuiInputTextFlags_CallbackCompletion:
        {
            // Example of TEXT COMPLETION

            // Locate beginning of current word
            const char* word_end = aData->Buf + aData->CursorPos;
            const char* word_start = word_end;
            while (word_start > aData->Buf)
            {
                const char c = word_start[-1];
                if (c == ' ' || c == '\t' || c == ',' || c == ';')
                    break;
                word_start--;
            }

            // Build a list of candidates
            ImVector<const char*> candidates;
            for (int i = 0; i < myCommands.size(); i++)
                if (strncmp(myCommands[i], word_start, (int)(word_end - word_start)) == 0)
                    candidates.push_back(myCommands[i]);

            if (candidates.Size == 0)
            {
                // No match
                AddLog("No match for \"%.*s\"!\n", (int)(word_end - word_start), word_start);
            }
            else if (candidates.Size == 1)
            {
                // Single match. Delete the beginning of the word and replace it entirely so we've got nice casing.
                aData->DeleteChars((int)(word_start - aData->Buf), (int)(word_end - word_start));
                aData->InsertChars(aData->CursorPos, candidates[0]);
                aData->InsertChars(aData->CursorPos, " ");
            }
            else
            {
                // Multiple matches. Complete as much as we can..
                // So inputing "C"+Tab will complete to "CL" then display "CLEAR" and "CLASSIFY" as matches.
                int match_len = (int)(word_end - word_start);
                for (;;)
                {
                    int c = 0;
                    bool all_candidates_matches = true;
                    for (int i = 0; i < candidates.Size && all_candidates_matches; i++)
                        if (i == 0)
                            c = toupper(candidates[i][match_len]);
                        else if (c == 0 || c != toupper(candidates[i][match_len]))
                            all_candidates_matches = false;
                    if (!all_candidates_matches)
                        break;
                    match_len++;
                }

                if (match_len > 0)
                {
                    aData->DeleteChars((int)(word_start - aData->Buf), (int)(word_end - word_start));
                    aData->InsertChars(aData->CursorPos, candidates[0], candidates[0] + match_len);
                }

                // List matches
                AddLog("Possible matches:\n");
                for (int i = 0; i < candidates.Size; i++)
                    AddLog("- %s\n", candidates[i]);
            }

            break;
        }
        case ImGuiInputTextFlags_CallbackHistory:
        {
            // Example of HISTORY
            const int prev_history_pos = myHistoryPosition;
            if (aData->EventKey == ImGuiKey_UpArrow)
            {
                if (myHistoryPosition == -1)
                    myHistoryPosition = static_cast<int>(myHistory.size()) - 1;
                else if (myHistoryPosition > 0)
                    myHistoryPosition--;
            }
            else if (aData->EventKey == ImGuiKey_DownArrow)
            {
                if (myHistoryPosition != -1)
                    if (++myHistoryPosition >= myHistory.size())
                        myHistoryPosition = -1;
            }

            // A better implementation would preserve the data on the current input line along with cursor position.
            if (prev_history_pos != myHistoryPosition)
            {
                const char* history_str = (myHistoryPosition >= 0) ? myHistory[myHistoryPosition] : "";
                aData->DeleteChars(0, aData->BufTextLen);
                aData->InsertChars(0, history_str);
            }
        }
    }
    return 0;
}
