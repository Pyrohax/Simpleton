#include "ConsoleWidget.h"
#include "../OpenGL/ConsoleO.h"
#include "../../Graphics/OpenGL/ImguiWrapper.h"

UI::ConsoleWidget::ConsoleWidget(ImguiWrapper* aWrapper, const std::string& aTitle)
    : Widget(aWrapper, aTitle)
    , myTitle(aTitle)
{
}

UI::ConsoleWidget::~ConsoleWidget()
{
}

void UI::ConsoleWidget::Tick()
{
    ConsoleO::GetInstance().Draw(myTitle.c_str());
}
