#pragma once

struct GLFWwindow;

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
	bool myShowDemoWindow;
};
