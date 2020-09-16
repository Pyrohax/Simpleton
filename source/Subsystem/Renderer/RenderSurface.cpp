#include "RenderSurface.h"

#include "Texture.h"
#include "../../Utility/Logger.h"

#include <GLFW/glfw3.h>
#include <cstdio>

RenderSurface::RenderSurface()
	: myWindow(nullptr)
	, myCurrentFrameTime(0.f)
	, myLastFrameTime(0.f)
	, myShouldClose(false)
	, myWidth(0)
	, myHeight(0)
{
	glfwSetErrorCallback(ErrorCallback);

	if (!glfwInit())
	{
		Log::Print(LogType::PROBLEM, "Failed to initialize GLFW");
		glfwTerminate();
		return;
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	myWindow = glfwCreateWindow(1240, 720, "Simpleton Editor", nullptr, nullptr);
	if (!myWindow)
	{
		Log::Print(LogType::PROBLEM, "Failed to open a GLFW window");
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(myWindow);

	glfwSetKeyCallback(myWindow, KeyCallback);

	glfwSetInputMode(myWindow, GLFW_STICKY_KEYS, GL_TRUE);

	glfwSwapInterval(1);

	PrintDebugInfo();

	myCurrentFrameTime = glfwGetTime();
	myLastFrameTime = myCurrentFrameTime;
}

RenderSurface::~RenderSurface()
{
}

void RenderSurface::PrintDebugInfo()
{
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	Log::Print(LogType::MESSAGE, "GLFW %d.%d.%d", major, minor, revision);
}

void RenderSurface::Tick()
{
	if (glfwWindowShouldClose(myWindow))
		myShouldClose = true;

	myCurrentFrameTime = glfwGetTime();
	myLastFrameTime = myCurrentFrameTime;

	glfwGetFramebufferSize(myWindow, &myWidth, &myHeight);

	glfwSwapBuffers(myWindow);

	glfwPollEvents();
}

void RenderSurface::Destroy()
{
	glfwDestroyWindow(myWindow);
	glfwTerminate();
}

void RenderSurface::SetWindowIcon(const Texture& aTexture)
{
	GLFWimage processIcon[1];
	processIcon[0].pixels = aTexture.mySource;
	processIcon[0].width = aTexture.myWidth;
	processIcon[0].height = aTexture.myHeight;
	glfwSetWindowIcon(myWindow, 1, processIcon);
}

void RenderSurface::ErrorCallback(int anError, const char* aDescription)
{
	Log::Print(LogType::MESSAGE, "%i %s", anError, aDescription);
}

void RenderSurface::KeyCallback(GLFWwindow* aWindow, int aKey, int /*aScancode*/, int anAction, int /*aMode*/)
{
	if (aKey == GLFW_KEY_ESCAPE && anAction == GLFW_PRESS)
		glfwSetWindowShouldClose(aWindow, GL_TRUE);
}
