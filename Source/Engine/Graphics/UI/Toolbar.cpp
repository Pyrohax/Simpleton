#include "Toolbar.h"
#include "ImguiExtension.h"
#include "../../Graphics/OpenGL/ImguiWrapper.h"

#include <functional>

UI::Toolbar::Toolbar(ImguiWrapper* aWrapper) : Widget(aWrapper)
{
	//myWidgetMap[Console] = 
}

void UI::Toolbar::Tick()
{
    auto showButton = [this](WidgetIconType anIconType, const std::function<bool()>& aGetvisibility, const std::function<void()>& aMakeVisible)
    {
        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_Button, aGetvisibility() ? ImGui::GetStyle().Colors[ImGuiCol_ButtonActive] : ImGui::GetStyle().Colors[ImGuiCol_Button]);

        if (ImageButton(anIconType, 20.0f))
            aMakeVisible();

        ImGui::PopStyleColor();
    };

    if (ImGui::BeginMainMenuBar())
    {
        for (auto& widgetReference : myWidgetMap)
        {
            Widget* widget = widgetReference.second;
            const WidgetIconType widgetIconType = widgetReference.first;

            showButton(widgetIconType, [this, &widget]() { return widget->GetIsVisible(); }, [this, &widget]() { widget->SetIsVisible(true); });
        }

        ImGui::EndMainMenuBar();
    }
}
