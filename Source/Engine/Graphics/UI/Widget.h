#pragma once

#include "imgui.h"

#include <string>

class ImguiWrapper;

namespace UI
{
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

		bool& GetIsVisible() { return myIsVisible; }
		void SetIsVisible(bool aValue) { myIsVisible = aValue; }
		void ToggleVisiblity() { myIsVisible = !myIsVisible; }

	private:
		ImguiWrapper* myWrapper;
		std::string myTitle;
		int myVarPushes;
		bool myIsVisible;
	};
}