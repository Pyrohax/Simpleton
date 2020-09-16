#pragma once

struct GLFWwindow;
struct Texture;

class RenderSurface
{
public:
	RenderSurface();
	~RenderSurface();

	void PrintDebugInfo();
	void Tick();
	void Destroy();

	void SetWindowIcon(const Texture& aTexture);

	static void ErrorCallback(int anError, const char* aDescription);
	static void KeyCallback(GLFWwindow* aWindow, int aKey, int aScancode, int anAction, int aMode);

	int GetScreenWidth() const { return myWidth; }
	int GetScreenHeight() const { return myHeight; }
	float GetScreenRatio() const { return myWidth / (float)myHeight; }
	double GetDeltaTime() const { return myCurrentFrameTime - myLastFrameTime; }
	GLFWwindow* GetWindow() const { return myWindow; }
	bool GetShouldClose() const { return myShouldClose; }

private:
	GLFWwindow* myWindow;
	double myCurrentFrameTime;
	double myLastFrameTime;
	bool myShouldClose;
	int myWidth;
	int myHeight;
};
