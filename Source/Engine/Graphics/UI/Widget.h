#pragma once

#include "../../Dependencies/imgui/imgui.h"

#include <string>

namespace UI
{
	class ImguiWrapper;

	class Widget
	{
	public:
		Widget(ImguiWrapper* aWrapper, const std::string& aTitle, bool anIsVisible = false);
		virtual ~Widget() = default;

		bool Begin();
		virtual void Tick() = 0;
		bool End();

		template<typename T>
		void PushStyleVar(ImGuiStyleVar anIndex, T aValue) { ImGui::PushStyleVar(anIndex, aValue); myVarPushes++; }

		void SetIsVisible(bool aValue) { myIsVisible = aValue; }
		void ToggleVisiblity() { myIsVisible = !myIsVisible; }

		bool& GetIsVisible() { return myIsVisible; }
		const std::string& GetTitle() const { return myTitle; }

	private:
		ImguiWrapper* myWrapper;
		std::string myTitle;
		int myVarPushes;
		bool myIsVisible;
	};
}
