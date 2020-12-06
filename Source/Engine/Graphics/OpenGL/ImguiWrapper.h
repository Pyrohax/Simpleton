#pragma once

#include "../../Graphics/UI/Widget.h"

#include <memory>

struct GLFWwindow;
class ImguiTitleBar;
class ImguiDebugWidget;
class Toolbar;

#include <vector>

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

	template<typename T>
	T* GetWidget()
	{
		for (const auto& widget : myWidgets)
		{
			if (T* widgetTemplate = dynamic_cast<T*>(widget.get()))
			{
				return widgetTemplate;
			}
		}

		return nullptr;
	}

private:
	std::vector<std::shared_ptr<UI::Widget>> myWidgets;
	Toolbar* myToolbar;
	ImguiTitleBar* myImguiTitleBar;
	ImguiDebugWidget* myDebugWidget;
	bool myShowTitleBar;
	bool myShowConsole;
	bool myShowDemo;
	bool myShowDebugWidget;
	bool myShowCamera;
};
