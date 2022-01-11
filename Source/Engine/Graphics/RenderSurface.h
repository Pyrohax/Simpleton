#pragma once

#include "GraphicsDefines.h"

struct GLFWwindow;
struct Texture;

class RenderSurface
{
public:
	RenderSurface(const int aWidth, const int aHeight)
		: myWindow(nullptr)
		, myWidth(aWidth)
		, myHeight(aHeight)
		, myShouldClose(false)
	{}

	virtual bool Initialize() = 0;
	virtual void Tick(const float aDeltaTime) = 0;
	virtual void Destroy() = 0;

	virtual void SetWindowIcon(const Texture& aTexture) = 0;

	int GetScreenWidth() const { return myWidth; }
	int GetScreenHeight() const { return myHeight; }
	float GetScreenRatio() const { return myWidth / static_cast<float>(myHeight); }
	GLFWwindow* GetWindow() const { return myWindow; }
	bool GetShouldClose() const { return myShouldClose; }

protected:
	virtual void PrintDebugInfo() = 0;

	GLFWwindow* myWindow;
	int myWidth;
	int myHeight;
	bool myShouldClose;
};
