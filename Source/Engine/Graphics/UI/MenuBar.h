#pragma once

#include "../../Submodules/imgui/imgui.h"

#include <string>

namespace UI
{
	class ImguiWrapper;

	class MenuBar
	{
	public:
		MenuBar(ImguiWrapper* aWrapper, bool anIsVisible = false);
		virtual ~MenuBar() = default;

		bool Begin();
		virtual void Tick() = 0;
		bool End();

		template<typename T>
		void PushStyleVar(ImGuiStyleVar anIndex, T aValue) { ImGui::PushStyleVar(anIndex, aValue); myVarPushes++; }

		bool& GetIsVisible() { return myIsVisible; }
		void SetIsVisible(bool aValue) { myIsVisible = aValue; }
		void ToggleVisiblity() { myIsVisible = !myIsVisible; }

	private:
		ImguiWrapper* myWrapper;
		int myVarPushes;
		bool myIsVisible;
	};
}
