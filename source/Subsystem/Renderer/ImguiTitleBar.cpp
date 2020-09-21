#include "ImguiTitleBar.h"

#include "imgui.h"

ImguiTitleBar::ImguiTitleBar()
{
}

ImguiTitleBar::~ImguiTitleBar()
{
}

void ImguiTitleBar::Draw(bool* aShowConsole, bool* aShowDemo)
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            ImGui::MenuItem("(demo menu)", NULL, false, false);
            if (ImGui::MenuItem("New")) {}
            if (ImGui::MenuItem("Open", "Ctrl+O")) {}
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Tools"))
        {
            if (ImGui::Button("Console"))
                *aShowConsole = true;

            ImGui::EndMenu();
        }
        if (ImGui::Button("Demo"))
        {
            *aShowDemo = true;
        }
       
        ImGui::EndMainMenuBar();
    }
}
