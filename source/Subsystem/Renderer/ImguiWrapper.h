#pragma once

struct GLFWwindow;
class ImguiTitleBar;

class ImguiWrapper
{
public:
	ImguiWrapper();
	~ImguiWrapper();

	void Initialize(GLFWwindow* aWindow);
	void CreateFrame();
	void Render();
	void Draw();
	void Destroy();

private:
	ImguiTitleBar* myImguiTitleBar;
	bool myShowTitleBar;
	bool myShowConsole;
	bool myShowDemo;
};
