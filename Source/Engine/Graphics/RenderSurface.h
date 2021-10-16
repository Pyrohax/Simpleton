#pragma once

#include "GraphicsDefines.h"

struct GLFWwindow;
struct Texture;

class RenderSurface
{
public:
	RenderSurface(const GraphicsAPI aGraphicsAPI, const int aWidth, const int aHeight)
		: myWindow(nullptr)
		, myGraphicsAPI(aGraphicsAPI)
		, myWidth(aWidth)
		, myHeight(aHeight)
		, myShouldClose(false)
	{}

	virtual void  Initialize() = 0;
	virtual void  Tick(double aDeltaTime) = 0;
	virtual void  Destroy() = 0;

	virtual void SetWindowIcon(const Texture& aTexture) = 0;

	int GetScreenWidth() const { return myWidth; }
	int GetScreenHeight() const { return myHeight; }
	float GetScreenRatio() const { return myWidth / static_cast<float>(myHeight); }
	GLFWwindow* GetWindow() const { return myWindow; }
	bool GetShouldClose() const { return myShouldClose; }

protected:
	virtual void PrintDebugInfo() = 0;
	static void ErrorCallback(int anError, const char* aDescription);
	static void KeyCallback(GLFWwindow* aWindow, int aKey, int aScancode, int anAction, int aMode);
	static void CursorCallback(GLFWwindow* aWindow, double aXPosition, double aYPosition);
	static void ScrollCallback(GLFWwindow* aWindow, double aXOffset, double aYOffset);
	static void MouseButtonCallback(GLFWwindow* aWindow, int aButton, int anAction, int aModifiers);

	GLFWwindow* myWindow;
	GraphicsAPI myGraphicsAPI;
	int myWidth;
	int myHeight;
	bool myShouldClose;
};
