#pragma once

#include "../../Graphics/UI/MenuBar.h"
#include "../../Graphics/UI/Widget.h"

#include <memory>
#include <vector>

struct GLFWwindow;

namespace UI
{
	class ImguiWrapper
	{
	public:
		ImguiWrapper();
		~ImguiWrapper();

		void Initialize(GLFWwindow* aWindow);
		void CreateFrame();
		void Render(double aDeltaTime);
		void Draw();
		void Destroy();

		template<typename Type>
		Type* GetWidget()
		{
			for (const auto& widget : myWidgets)
			{
				if (Type* widgetTemplate = dynamic_cast<Type*>(widget.get()))
				{
					return widgetTemplate;
				}
			}

			return nullptr;
		}

		template<typename Type>
		Type* GetMenuBar()
		{
			for (const auto& menuBar : myMenuBars)
			{
				if (Type* menuBarTemplate = dynamic_cast<Type*>(menuBar.get()))
				{
					return menuBarTemplate;
				}
			}

			return nullptr;
		}

	private:
		std::vector<std::shared_ptr<UI::Widget>> myWidgets;
		std::vector<std::shared_ptr<UI::MenuBar>> myMenuBars;
	};
}
