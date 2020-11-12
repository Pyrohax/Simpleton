#include "ImguiWrapper.h"

#include "ImguiDebugWidget.h"
#include "ImguiTitleBar.h"
#include "Console.h"
#include "../../World/Camera.h"

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

#include <GLFW/glfw3.h>

ImguiWrapper::ImguiWrapper()
    : myShowTitleBar(true)
    , myShowConsole(false)
    , myShowDemo(false)
    , myShowDebugWidget(false)
    , myShowCamera(false)
{
    myImguiTitleBar = new ImguiTitleBar();
    myDebugWidget = new ImguiDebugWidget();
    auto imguiTitleBar = std::bind(&ImguiTitleBar::Draw, myImguiTitleBar);
    myCamera = new Camera();
    std::function<void()> camera = std::bind(&Camera::DrawDebug, myCamera);
    myBindings.push_back(camera);
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
    ImGui_ImplOpenGL3_Init("#version 330");
}

void ImguiWrapper::CreateFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImguiWrapper::Render(double aDeltaTime)
{
    for (auto& binding : myBindings)
    {
        binding();
    }

    if (myShowTitleBar)
        myImguiTitleBar->Draw(&myShowConsole, &myShowDemo, &myShowDebugWidget);

    if (myShowConsole)
        Console::GetInstance().Draw("Console", &myShowConsole);

    if (myShowDemo)
        ImGui::ShowDemoWindow(&myShowDemo);

    if (myShowDebugWidget)
        myDebugWidget->Draw(aDeltaTime);

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
