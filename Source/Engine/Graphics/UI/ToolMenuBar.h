#pragma once

#include "MenuBar.h"
#include "Widget.h"

#include <unordered_map>

namespace UI
{
    class ImguiWrapper;
    enum class WidgetIconType;

    class ToolMenuBar : public MenuBar
    {
    public:
        ToolMenuBar(ImguiWrapper* aWrapper);

        void Tick() override;

    private:
        std::unordered_map<WidgetIconType, Widget*> myWidgetMap;
        std::string myTitle;
    };
}
