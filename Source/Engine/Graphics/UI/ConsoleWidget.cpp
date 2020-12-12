#include "ConsoleWidget.h"

#include "ImguiWrapper.h"
#include "../../Core/Time.h"

#define ERROR_PREFIX "(P)"
#define SUCCES_PREFIX "(S)"

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
    ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);

    //ImGui::TextWrapped("Press TAB for auto-completion. Press UP/DOWN to navigate history.");
    //ImGui::TextWrapped("Enter 'HELP' for help.");

    //// TODO: display items starting from the bottom

    //if (ImGui::SmallButton("Clear")) { ClearLog(); }
    //ImGui::SameLine();
    //bool copy_to_clipboard = ImGui::SmallButton("Copy");
    ////static float t = 0.0f; if (ImGui::GetTime() - t > 0.02f) { t = ImGui::GetTime(); AddLog("Spam %f", t); }

    //ImGui::Separator();

    //// Options menu
    //if (ImGui::BeginPopup("Options"))
    //{
    //    ImGui::Checkbox("Auto-scroll", &myAutoScroll);
    //    ImGui::EndPopup();
    //}

    //// Options, Filter
    //if (ImGui::Button("Options"))
    //    ImGui::OpenPopup("Options");
    //ImGui::SameLine();
    //myFilter->Draw("Filter (\"incl,-excl\") (\"error\")", 180);
    //ImGui::Separator();

    //// Reserve enough left-over height for 1 separator + 1 input text
    //const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
    //ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar);
    //if (ImGui::BeginPopupContextWindow())
    //{
    //    if (ImGui::Selectable("Clear")) ClearLog();
    //    ImGui::EndPopup();
    //}

    //// Display every line as a separate entry so we can change their color or add custom widgets.
    //// If you only want raw text you can use ImGui::TextUnformatted(log.begin(), log.end());
    //// NB- if you have thousands of entries this approach may be too inefficient and may require user-side clipping
    //// to only process visible items. The clipper will automatically measure the height of your first item and then
    //// "seek" to display only items in the visible area.
    //// To use the clipper we can replace your standard loop:
    ////      for (int i = 0; i < Items.Size; i++)
    ////   With:
    ////      ImGuiListClipper clipper(Items.Size);
    ////      while (clipper.Step())
    ////         for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
    //// - That your items are evenly spaced (same height)
    //// - That you have cheap random access to your elements (you can access them given their index,
    ////   without processing all the ones before)
    //// You cannot this code as-is if a filter is active because it breaks the 'cheap random-access' property.
    //// We would need random-access on the post-filtered list.
    //// A typical application wanting coarse clipping and filtering may want to pre-compute an array of indices
    //// or offsets of items that passed the filtering test, recomputing this array when user changes the filter,
    //// and appending newly elements as they are inserted. This is left as a task to the user until we can manage
    //// to improve this example code!
    //// If your items are of variable height:
    //// - Split them into same height items would be simpler and facilitate random-seeking into your list.
    //// - Consider using manual call to IsRectVisible() and skipping extraneous decoration from your items.
    //ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
    //if (copy_to_clipboard)
    //    ImGui::LogToClipboard();
    //for (int i = 0; i < myItems.size(); i++)
    //{
    //    const char* item = myItems[i];
    //    if (!myFilter->PassFilter(item))
    //        continue;

    //    // Normally you would store more information in your item than just a string.
    //    // (e.g. make Items[] an array of structure, store color/type etc.)
    //    ImVec4 color;
    //    bool has_color = false;
    //    if (strstr(item, ERROR_PREFIX)) { color = ImVec4(1.0f, 0.4f, 0.4f, 1.0f); has_color = true; }
    //    else if (strstr(item, SUCCES_PREFIX)) { color = ImVec4(0.4f, 1.0f, 0.4f, 1.0f); has_color = true; }
    //    else if (strncmp(item, "# ", 2) == 0) { color = ImVec4(1.0f, 0.8f, 0.6f, 1.0f); has_color = true; }
    //    if (has_color)
    //        ImGui::PushStyleColor(ImGuiCol_Text, color);
    //    ImGui::TextUnformatted(item);
    //    if (has_color)
    //        ImGui::PopStyleColor();
    //}
    //if (copy_to_clipboard)
    //    ImGui::LogFinish();

    //if (myScrollToBottom || (myAutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
    //    ImGui::SetScrollHereY(1.0f);
    //myScrollToBottom = false;

    //ImGui::PopStyleVar();
    //ImGui::EndChild();
    //ImGui::Separator();

    static ImGuiTableColumnFlags column_flags = ImGuiTableColumnFlags_WidthFixed | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY | ImGuiTableFlags_BordersOuter | ImGuiTableColumnFlags_DefaultSort | ImGuiTableFlags_Sortable;
    const char* column_names[4] = { "Time", "Severity", "Category", "Message" };
    if (ImGui::BeginTable("##Logs", 4, column_flags))
    {
        ImGui::TableSetupColumn(column_names[0], column_flags);
        ImGui::TableSetupColumn(column_names[1], column_flags);
        ImGui::TableSetupColumn(column_names[2], column_flags);
        ImGui::TableSetupColumn(column_names[3], column_flags);
        ImGui::TableHeadersRow();

        for (auto& item : myItems)
        {
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("%s", item.myTimestamp.c_str());
            ImGui::TableNextColumn();
            ImGui::Text("%s", Log::GetSeverityAsString(item.mySeverity).c_str());
            ImGui::TableNextColumn();
            ImGui::Text("%s", Log::GetCategoryAsString(item.myCategory).c_str());
            ImGui::TableNextColumn();
            ImGui::Text("%s", item.myMessage.c_str());
        }

        ImGui::EndTable();
    }

    //// Command-line
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
