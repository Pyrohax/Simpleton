#include "Widget.h"

#include "../../Graphics/OpenGL/ImguiWrapper.h"

namespace UI
{
	Widget::Widget(ImguiWrapper* aWrapper, const std::string& aTitle, bool anIsVisible)
		: myWrapper(aWrapper)
		, myTitle(aTitle)
		, myVarPushes(0)
		, myIsVisible(anIsVisible)
	{
	}

	bool Widget::Begin()
	{
		if (!GetIsVisible())
			return false;

		ImGui::Begin(myTitle.c_str(), &myIsVisible);

		return true;
	}

	bool Widget::End()
	{
		/*ImGui::PopStyleVar(myVarPushes);
		myVarPushes = 0;*/

		ImGui::End();

		return true;
	}
}
