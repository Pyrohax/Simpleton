#pragma once

#include "GraphicsDefines.h"

struct GLFWwindow;
struct Texture;
typedef struct VkInstance_T* VkInstance;

class RenderSurface
{
public:
	RenderSurface();
	~RenderSurface();

	void Initialize(GraphicsAPI aGraphicsAPI);
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
	static void MouseButtonCallback(GLFWwindow* aWindow, int aButton, int anAction, int aModifiers);

private:
	GLFWwindow* myWindow;
	VkInstance myVulkanInstance;
	bool myShouldClose;
	int myWidth;
	int myHeight;
};
