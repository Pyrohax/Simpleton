#pragma once

#include "Widget.h"

class ImguiWrapper;

namespace UI
{
    enum class WidgetIconType;

    class CameraWidget : public Widget
    {
    public:
        CameraWidget(ImguiWrapper* aWrapper, const std::string& aTitle);

        void Tick() override;
    };
}
