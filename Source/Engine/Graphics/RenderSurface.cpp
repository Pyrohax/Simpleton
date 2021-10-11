#include "RenderSurface.h"

#include "Texture.h"
#include "../Core/Logger.h"
#include "../Core/InputManager.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <cstdio>
#include <map>

RenderSurface::RenderSurface()
	: myWindow(nullptr)
	, myShouldClose(false)
	, myWidth(1280)
	, myHeight(720)
{
}

RenderSurface::~RenderSurface()
{
}

void RenderSurface::Initialize(GraphicsAPI aGraphicsAPI)
{
	glfwSetErrorCallback(ErrorCallback);

	if (!glfwInit())
	{
		Log::Logger::Print(Log::Severity::Error, Log::Category::Rendering, "Failed to initialize GLFW");
		glfwTerminate();
		return;
	}

	if (aGraphicsAPI == GraphicsAPI::Vulkan)
	{
		if (!glfwVulkanSupported())
		{
			Log::Logger::Print(Log::Severity::Error, Log::Category::Rendering, "Failed to use Vulkan with GLFW");
			glfwTerminate();
			return;
		}

		VkApplicationInfo vulkanAppInfo{};
		vulkanAppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		vulkanAppInfo.pApplicationName = "Simpleton Editor";
		vulkanAppInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		vulkanAppInfo.pEngineName = "Simpleton";
		vulkanAppInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		vulkanAppInfo.apiVersion = VK_API_VERSION_1_0;

		//PFN_vkCreateInstance pfnCreateInstance = (PFN_vkCreateInstance)glfwGetInstanceProcAddress(myVulkanInstance, "vkCreateInstance");
		//PFN_vkCreateDevice pfnCreateDevice = (PFN_vkCreateDevice)glfwGetInstanceProcAddress(myVulkanInstance, "vkCreateDevice");
		//PFN_vkGetDeviceProcAddr pfnGetDeviceProcAddr = (PFN_vkGetDeviceProcAddr)glfwGetInstanceProcAddress(myVulkanInstance, "vkGetDeviceProcAddr");
		uint32_t count;
		const char** extensions = glfwGetRequiredInstanceExtensions(&count);

		VkInstanceCreateInfo vulkanInstanceCreateInfo{};
		vulkanInstanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		vulkanInstanceCreateInfo.enabledExtensionCount = count;
		vulkanInstanceCreateInfo.ppEnabledExtensionNames = extensions;
		vulkanInstanceCreateInfo.pApplicationInfo = &vulkanAppInfo;
		vulkanInstanceCreateInfo.enabledLayerCount = 0;

		if (vkCreateInstance(&vulkanInstanceCreateInfo, nullptr, &myVulkanInstance) != VK_SUCCESS)
		{
			Log::Logger::Print(Log::Severity::Error, Log::Category::Rendering, "Failed to create Vulkan instance");
			glfwTerminate();
			return;
		}

		VkPhysicalDevice vulkanPhysicalDevice = VK_NULL_HANDLE;
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(myVulkanInstance, &deviceCount, nullptr);
		if (deviceCount == 0)
		{
			Log::Logger::Print(Log::Severity::Error, Log::Category::Rendering, "Failed to detect physical device presentation support");
			glfwTerminate();
			return;
		}

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(myVulkanInstance, &deviceCount, devices.data());
		vulkanPhysicalDevice = devices[0];

		if (glfwGetPhysicalDevicePresentationSupport(myVulkanInstance, vulkanPhysicalDevice, 0) != GLFW_TRUE)
		{
			Log::Logger::Print(Log::Severity::Error, Log::Category::Rendering, "Failed to detect physical device presentation support");
			glfwTerminate();
			return;
		}
	}

	switch (aGraphicsAPI)
	{
		case GraphicsAPI::None:
		{
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			break;
		}
		case GraphicsAPI::DirectX12:
		{
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			break;
		}
		case GraphicsAPI::OpenGL:
		{
			glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
			break;
		}
		case GraphicsAPI::Vulkan:
		{
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			break;
		}
	}
	
	glfwWindowHint(GLFW_SAMPLES, 4);

	myWindow = glfwCreateWindow(myWidth, myHeight, "Simpleton Editor", nullptr, nullptr);
	if (!myWindow)
	{
		Log::Logger::Print(Log::Severity::Error, Log::Category::Rendering, "Failed to open a GLFW window");
		glfwTerminate();
		return;
	}

	if (aGraphicsAPI == GraphicsAPI::Vulkan)
	{
		VkSurfaceKHR vulkanSurface;
		if (glfwCreateWindowSurface(myVulkanInstance, myWindow, nullptr, &vulkanSurface) != VK_SUCCESS)
		{
			Log::Logger::Print(Log::Severity::Error, Log::Category::Rendering, "Failed to open a GLFW window");
			glfwTerminate();
			return;
		}
	}

	glfwMakeContextCurrent(myWindow);
	glfwSetWindowUserPointer(myWindow, this);
	glfwSetKeyCallback(myWindow, KeyCallback);
	glfwSetInputMode(myWindow, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetCursorPosCallback(myWindow, CursorCallback);
	glfwSetInputMode(myWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(myWindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	glfwSetScrollCallback(myWindow, ScrollCallback);
	glfwSetMouseButtonCallback(myWindow, MouseButtonCallback);
	glfwSwapInterval(1);

	PrintDebugInfo();
}

void RenderSurface::Tick(double aDeltaTime)
{
	glfwPollEvents();

	if (InputManager::GetInstance().GetIsKeyDown(Keys::Escape))
	{
		glfwSetWindowShouldClose(myWindow, true);
	}

	if (glfwWindowShouldClose(myWindow))
		myShouldClose = true;

	glfwGetFramebufferSize(myWindow, &myWidth, &myHeight);
	glfwSwapBuffers(myWindow);
}

void RenderSurface::Destroy()
{
	vkDestroyInstance(myVulkanInstance, nullptr);
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

void RenderSurface::PrintDebugInfo()
{
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	Log::Logger::Print(Log::Severity::Message, Log::Category::Rendering, "GLFW %d.%d.%d", major, minor, revision);
	Log::Logger::Print(Log::Severity::Message, Log::Category::Rendering, "Window size %ix%i", myWidth, myHeight);
}

void RenderSurface::ErrorCallback(int anError, const char* aDescription)
{
	Log::Logger::Print(Log::Severity::Message, Log::Category::Rendering, "%i %s", anError, aDescription);
}

void RenderSurface::KeyCallback(GLFWwindow* aWindow, int aKey, int aScancode, int anAction, int aMode)
{
	InputManager::GetInstance().OnKeyAction(aKey, aScancode, anAction != GLFW_RELEASE, aMode);
}

void RenderSurface::CursorCallback(GLFWwindow* aWindow, double aXPosition, double aYPosition)
{
	InputManager::GetInstance().OnCursorAction(aXPosition, aYPosition);
}

void RenderSurface::ScrollCallback(GLFWwindow* aWindow, double aXOffset, double aYOffset)
{
	InputManager::GetInstance().OnScrollAction(aXOffset, aYOffset);
}

void RenderSurface::MouseButtonCallback(GLFWwindow* aWindow, int aButton, int anAction, int aModifiers)
{
	InputManager::GetInstance().OnMouseButtonAction(aButton, anAction, aModifiers);
}
