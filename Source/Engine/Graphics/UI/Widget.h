#pragma once

#include "imgui.h"

class ImguiWrapper;

namespace UI
{
	class Widget
	{
	public:
		Widget(ImguiWrapper* aWrapper);
		virtual ~Widget() = default;

		bool Begin();
		virtual void Tick() = 0;
		bool End();

		template<typename T>
		void PushStyleVar(ImGuiStyleVar anIndex, T aValue) { ImGui::PushStyleVar(anIndex, aValue); myVarPushes++; }

		bool GetIsVisible() const { return myIsVisible; }
		void SetIsVisible(bool aValue) { myIsVisible = aValue; }

	private:
		ImguiWrapper* myWrapper;
		int myVarPushes;
		bool myIsVisible;
	};
}
