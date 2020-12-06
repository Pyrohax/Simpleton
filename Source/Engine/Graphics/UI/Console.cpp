#include "Console.h"
#include "../OpenGL/ConsoleO.h"
#include "../../Graphics/OpenGL/ImguiWrapper.h"

UI::Console::Console(ImguiWrapper* aWrapper) : Widget(aWrapper)
{
}

UI::Console::~Console()
{
}

void UI::Console::Tick()
{
    ConsoleO::GetInstance().Draw("Console");
}
