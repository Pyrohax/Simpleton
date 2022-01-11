#pragma once

#include "../RenderSurface.h"

struct GLFWwindow;
struct Texture;

class OpenGLRenderSurface final : public RenderSurface
{
public:
	OpenGLRenderSurface(const int aWidth, const int aHeight);
	~OpenGLRenderSurface();

	bool Initialize() override;
	void Tick(const float aDeltaTime) override;
	void Destroy() override;

	void SetWindowIcon(const Texture& aTexture) override;

	int GetScreenWidth() const { return myWidth; }
	int GetScreenHeight() const { return myHeight; }
	float GetScreenRatio() const { return myWidth / (float)myHeight; }
	GLFWwindow* GetWindow() const { return myWindow; }
	bool GetShouldClose() const { return myShouldClose; }

private:
	void PrintDebugInfo() override;
	static void ErrorCallback(int anError, const char* aDescription);
	static void KeyCallback(GLFWwindow* aWindow, int aKey, int aScancode, int anAction, int aMode);
	static void CursorCallback(GLFWwindow* aWindow, double aXPosition, double aYPosition);
	static void ScrollCallback(GLFWwindow* aWindow, double aXOffset, double aYOffset);
	static void MouseButtonCallback(GLFWwindow* aWindow, int aButton, int anAction, int aModifiers);
};
