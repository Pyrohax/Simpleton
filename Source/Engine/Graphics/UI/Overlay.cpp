#include "Overlay.h"

#include "ImguiWrapper.h"

UI::Overlay::Overlay(bool anIsVisible)
	: myVarPushes(0)
	, myIsVisible(anIsVisible)
{
}

bool UI::Overlay::Begin()
{
	if (!GetIsVisible())
		return false;

	return true;
}

bool UI::Overlay::End()
{
	/*ImGui::PopStyleVar(myVarPushes);
	myVarPushes = 0;*/

	return true;
}
