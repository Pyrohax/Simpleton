#pragma once

#include "Widget.h"

#include <unordered_map>

class ImguiWrapper;

namespace UI
{
    enum class WidgetIconType;

    class Toolbar : public Widget
    {
    public:
        Toolbar(ImguiWrapper* aWrapper);

        void Tick() override;

    private:
        std::unordered_map<WidgetIconType, Widget*> myWidgetMap;
    };
}
