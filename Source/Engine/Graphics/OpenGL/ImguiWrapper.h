#pragma once

struct GLFWwindow;
class ImguiTitleBar;
class ImguiDebugWidget;
class Camera;

#include <functional>
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

private:
	ImguiTitleBar* myImguiTitleBar;
	ImguiDebugWidget* myDebugWidget;
	Camera* myCamera;
	bool myShowTitleBar;
	bool myShowConsole;
	bool myShowDemo;
	bool myShowDebugWidget;
	bool myShowCamera;
	std::vector<std::function<void()>> myBindings;
};
