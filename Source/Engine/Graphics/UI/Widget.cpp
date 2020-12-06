#include "Widget.h"

#include "../../Graphics/OpenGL/ImguiWrapper.h"

namespace UI
{
	Widget::Widget(ImguiWrapper* aWrapper)
		: myWrapper(aWrapper)
		, myVarPushes(0)
		, myIsVisible(true)
	{
	}

	bool Widget::Begin()
	{
		if (!GetIsVisible())
			return false;

		return true;
	}

	bool Widget::End()
	{
		ImGui::PopStyleVar(myVarPushes);
		myVarPushes = 0;

		return true;
	}
}
