#include "ToolMenuBar.h"
#include "ImguiExtension.h"
#include "../../Graphics/OpenGL/ImguiWrapper.h"

#include "CameraWidget.h"

#include <functional>

UI::ToolMenuBar::ToolMenuBar(ImguiWrapper* aWrapper)
    : MenuBar(aWrapper, true)
{
    myWidgetMap[WidgetIconType::Camera] = aWrapper->GetWidget<CameraWidget>();
    //myWidgetMap[WidgetIconType::Console] =
}

void UI::ToolMenuBar::Tick()
{
    auto showButton = [this](WidgetIconType anIconType, const std::string& aLabel, const std::function<bool()>& aGetvisibility, const std::function<void()>& aMakeVisible)
    {
        //ImGui::PushStyleColor(ImGuiCol_Button, aGetvisibility() ? ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] : ImGui::GetStyle().Colors[ImGuiCol_Button]);

        //if (ImageButton(anIconType, 20.0f))
            //aMakeVisible();

        if (ImGui::Button(aLabel.c_str()))
            aMakeVisible();

        //ImGui::PopStyleColor();
    };

    if (ImGui::BeginMainMenuBar())
    {
        for (auto& widgetReference : myWidgetMap)
        {
            Widget* widget = widgetReference.second;
            const WidgetIconType widgetIconType = widgetReference.first;

            showButton(widgetIconType, "Camera", [this, &widget]() { return widget->GetIsVisible(); }, [this, &widget]() { widget->ToggleVisiblity(); });
        }

        ImGui::EndMainMenuBar();
    }
}
