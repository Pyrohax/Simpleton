#include "ImguiWrapper.h"

#include "ImguiDebugWidget.h"
#include "ImguiTitleBar.h"
#include "ConsoleO.h"
#include "../../Graphics/UI/Console.h"
#include "../../Graphics/UI/Toolbar.h"
#include "../../Core/Engine.h"
#include "../../World/World.h"
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
    , myToolbar(nullptr)
{
    myDebugWidget = new ImguiDebugWidget();
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

    myWidgets.emplace_back(std::make_shared<UI::Toolbar>(this));
    myWidgets.emplace_back(std::make_shared<UI::Console>(this));
}

void ImguiWrapper::CreateFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImguiWrapper::Render(double aDeltaTime)
{
    for (auto& widget : myWidgets)
    {
        if (widget->Begin())
        {
            widget->Tick();
            widget->End();
        }
    }

    if (myShowDemo)
        ImGui::ShowDemoWindow(&myShowDemo);

    if (myShowDebugWidget)
        myDebugWidget->Draw(aDeltaTime);

    if (myShowCamera)
    {
        Engine& engine = Engine::GetInstance();
        World& world = *engine.GetWorld();
        world.GetCamera().DrawDebug();
    }

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
