#pragma once

#include "../../Dependencies/imgui/imgui.h"

#include <string>

namespace UI
{
	class ImguiWrapper;

	class Overlay
	{
	public:
		Overlay(bool anIsVisible = false);
		virtual ~Overlay() = default;

		bool Begin();
		virtual void Tick() = 0;
		bool End();

		template<typename T>
		void PushStyleVar(ImGuiStyleVar anIndex, T aValue) { ImGui::PushStyleVar(anIndex, aValue); myVarPushes++; }

		bool& GetIsVisible() { return myIsVisible; }
		void SetIsVisible(bool aValue) { myIsVisible = aValue; }
		void ToggleVisiblity() { myIsVisible = !myIsVisible; }

	private:
		int myVarPushes;
		bool myIsVisible;
	};
}
