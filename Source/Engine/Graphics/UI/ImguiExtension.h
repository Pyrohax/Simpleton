#pragma once

#include "WidgetIconType.h"

#include "imgui.h"

namespace UI
{
    inline bool ImageButton(const WidgetIconType anIconType, const float aSize)
    {
        return ImGui::ImageButton(
            //static_cast<ImTextureID>(IconProvider::Get().GetTextureByType(anIconType)),
            0,
            ImVec2(aSize, aSize),
            ImVec2(0.0f, 0.0f),
            ImVec2(1.0f, 1.0f),
            -1,
            ImColor(0, 0, 0, 0),
            ImVec4(255.0f, 255.0f, 255.0f, 255.0f)
        );
    }
}
