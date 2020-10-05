#pragma once

struct GLFWwindow;
struct Texture;

class RenderSurface
{
public:
	RenderSurface();
	~RenderSurface();

	void Initialize();
	void Tick(double aDeltaTime);
	void Destroy();

	void SetWindowIcon(const Texture& aTexture);

	int GetScreenWidth() const { return myWidth; }
	int GetScreenHeight() const { return myHeight; }
	float GetScreenRatio() const { return myWidth / (float)myHeight; }
	GLFWwindow* GetWindow() const { return myWindow; }
	bool GetShouldClose() const { return myShouldClose; }

private:
	void PrintDebugInfo();
	static void ErrorCallback(int anError, const char* aDescription);
	static void KeyCallback(GLFWwindow* aWindow, int aKey, int aScancode, int anAction, int aMode);
	static void CursorCallback(GLFWwindow* aWindow, double aXPosition, double aYPosition);
	static void ScrollCallback(GLFWwindow* aWindow, double aXOffset, double aYOffset);

private:
	GLFWwindow* myWindow;
	bool myShouldClose;
	int myWidth;
	int myHeight;
};
