#include "ImguiWrapper.h"

#include "../../Core/Engine.h"
#include "../../Graphics/UI/CameraWidget.h"
#include "../../Graphics/UI/ConsoleWidget.h"
#include "../../Graphics/UI/ToolMenuBar.h"
#include "../../World/World.h"

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

#include <GLFW/glfw3.h>

UI::ImguiWrapper::ImguiWrapper()
{
}

UI::ImguiWrapper::~ImguiWrapper()
{
}

void UI::ImguiWrapper::Initialize(GLFWwindow* aWindow)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(aWindow, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    myWidgets.emplace_back(std::make_shared<UI::CameraWidget>(this, "Camera"));
    myWidgets.emplace_back(std::make_shared<UI::ConsoleWidget>(this, "Console"));
    myMenuBars.emplace_back(std::make_shared<UI::ToolMenuBar>(this));
}

void UI::ImguiWrapper::AddOverlay(const std::shared_ptr<UI::Overlay>& anOverlay)
{
    myOverlays.emplace_back(anOverlay);
}

void UI::ImguiWrapper::CreateFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UI::ImguiWrapper::Render(double aDeltaTime)
{
    for (auto& widget : myWidgets)
    {
        if (widget->Begin())
        {
            widget->Tick();
            widget->End();
        }
    }

    for (auto& menuBar : myMenuBars)
    {
        if (menuBar->Begin())
        {
            menuBar->Tick();
            menuBar->End();
        }
    }

    for (auto& overlay : myOverlays)
    {
        if (overlay->Begin())
        {
            overlay->Tick();
            overlay->End();
        }
    }

    ImGui::Render();
}

void UI::ImguiWrapper::Draw()
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::ImguiWrapper::Destroy()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
