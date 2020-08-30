#pragma once

struct GLFWwindow;

class RenderSurface
{
public:
	RenderSurface();
	~RenderSurface();

	void PrintDebugInfo();

	void Tick();

	void Destroy();

	static void ErrorCallback(int anError, const char* aDescription);

	static void KeyCallback(GLFWwindow* aWindow, int aKey, int aScancode, int anAction, int aMode);

	int GetScreenWidth() { return myWidth; }

	int GetScreenHeight() { return myHeight; }

	float GetScreenRatio() { return myWidth / (float)myHeight; }

	double GetDeltaTime() { return myCurrentFrameTime - myLastFrameTime; }

	bool myShouldClose;

private:
	GLFWwindow* myWindow;
	double myCurrentFrameTime;
	double myLastFrameTime;
	int myWidth;
	int myHeight;
};
