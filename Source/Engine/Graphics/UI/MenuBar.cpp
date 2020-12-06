#include "MenuBar.h"

#include "../../Graphics/OpenGL/ImguiWrapper.h"

UI::MenuBar::MenuBar(ImguiWrapper* aWrapper, bool anIsVisible)
	: myWrapper(aWrapper)
	, myVarPushes(0)
	, myIsVisible(anIsVisible)
{
}

bool UI::MenuBar::Begin()
{
	if (!GetIsVisible())
		return false;

	return true;
}

bool UI::MenuBar::End()
{
	/*ImGui::PopStyleVar(myVarPushes);
	myVarPushes = 0;*/

	return true;
}
