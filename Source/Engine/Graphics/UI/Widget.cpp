#include "Widget.h"

#include "ImguiWrapper.h"

UI::Widget::Widget(ImguiWrapper* aWrapper, const std::string& aTitle, bool anIsVisible)
	: myWrapper(aWrapper)
	, myTitle(aTitle)
	, myVarPushes(0)
	, myIsVisible(anIsVisible)
{
}

bool UI::Widget::Begin()
{
	if (!GetIsVisible())
		return false;

	ImGui::Begin(myTitle.c_str(), &myIsVisible);

	return true;
}

bool UI::Widget::End()
{
	/*ImGui::PopStyleVar(myVarPushes);
	myVarPushes = 0;*/

	ImGui::End();

	return true;
}