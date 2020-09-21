#include "ImguiWrapper.h"

#include "ImguiTitleBar.h"
#include "Console.h"

#include "imgui.h"
#include "examples/imgui_impl_opengl3.h"
#include "examples/imgui_impl_glfw.h"

#include <GLFW/glfw3.h>

ImguiWrapper::ImguiWrapper()
    : myShowTitleBar(true)
    , myShowConsole(false)
    , myShowDemo(false)
{
    myImguiTitleBar = new ImguiTitleBar();
}

ImguiWrapper::~ImguiWrapper()
{
}

void ImguiWrapper::Initialize(GLFWwindow* aWindow)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(aWindow, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void ImguiWrapper::CreateFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImguiWrapper::Render()
{
    if (myShowTitleBar)
        myImguiTitleBar->Draw(&myShowConsole, &myShowDemo);

    if (myShowConsole)
        Console::GetInstance().Draw("Console", &myShowConsole);

    if (myShowDemo)
        ImGui::ShowDemoWindow(&myShowDemo);

    ImGui::Render();
}

void ImguiWrapper::Draw()
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImguiWrapper::Destroy()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
