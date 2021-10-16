#include "VulkanRenderSurface.h"

#include "../../Core/InputManager.h"
#include "../../Core/Logger.h"
#include "../Texture.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

VulkanRenderSurface::VulkanRenderSurface(const GraphicsAPI aGraphicsAPI, const int aWidth, const int aHeight)
	: RenderSurface(aGraphicsAPI, aWidth, aHeight)
	, myVulkanInstance(nullptr)
	, myVulkanPhysicalDevice(nullptr)
{}

VulkanRenderSurface::~VulkanRenderSurface()
{}

void VulkanRenderSurface::Initialize()
{
	glfwSetErrorCallback(ErrorCallback);

	if (!glfwInit())
	{
		Log::Logger::Print(Log::Severity::Error, Log::Category::Rendering, "Failed to initialize GLFW");
		glfwTerminate();
		return;
	}

	if (!glfwVulkanSupported())
	{
		Log::Logger::Print(Log::Severity::Error, Log::Category::Rendering, "Failed to use Vulkan with GLFW");
		glfwTerminate();
		return;
	}

	CreateVulkanInstance();
	SetupVulkanPhysicalDevice();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_SAMPLES, 4);

	myWindow = glfwCreateWindow(myWidth, myHeight, "Simpleton Editor (Vulkan)", nullptr, nullptr);
	if (!myWindow)
	{
		Log::Logger::Print(Log::Severity::Error, Log::Category::Rendering, "Failed to open a GLFW window");
		glfwTerminate();
		return;
	}

	VkSurfaceKHR vulkanSurface;
	if (glfwCreateWindowSurface(myVulkanInstance, myWindow, nullptr, &vulkanSurface) != VK_SUCCESS)
	{
		Log::Logger::Print(Log::Severity::Error, Log::Category::Rendering, "Failed to open a GLFW window");
		glfwTerminate();
		return;
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

void VulkanRenderSurface::Tick(double aDeltaTime)
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

void VulkanRenderSurface::Destroy()
{
	vkDestroyInstance(myVulkanInstance, nullptr);
	glfwDestroyWindow(myWindow);
	glfwTerminate();
}

void VulkanRenderSurface::SetWindowIcon(const Texture& aTexture)
{
	GLFWimage processIcon[1];
	processIcon[0].pixels = aTexture.mySource;
	processIcon[0].width = aTexture.myWidth;
	processIcon[0].height = aTexture.myHeight;
	glfwSetWindowIcon(myWindow, 1, processIcon);
}

void VulkanRenderSurface::PrintDebugInfo()
{
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	Log::Logger::Print(Log::Severity::Message, Log::Category::Rendering, "GLFW %d.%d.%d", major, minor, revision);
	Log::Logger::Print(Log::Severity::Message, Log::Category::Rendering, "Window size %ix%i", myWidth, myHeight);
}

void VulkanRenderSurface::ErrorCallback(int anError, const char* aDescription)
{
	Log::Logger::Print(Log::Severity::Message, Log::Category::Rendering, "%i %s", anError, aDescription);
}

void VulkanRenderSurface::KeyCallback(GLFWwindow* aWindow, int aKey, int aScancode, int anAction, int aMode)
{
	InputManager::GetInstance().OnKeyAction(aKey, aScancode, anAction != GLFW_RELEASE, aMode);
}

void VulkanRenderSurface::CursorCallback(GLFWwindow* aWindow, double aXPosition, double aYPosition)
{
	InputManager::GetInstance().OnCursorAction(aXPosition, aYPosition);
}

void VulkanRenderSurface::ScrollCallback(GLFWwindow* aWindow, double aXOffset, double aYOffset)
{
	InputManager::GetInstance().OnScrollAction(aXOffset, aYOffset);
}

void VulkanRenderSurface::MouseButtonCallback(GLFWwindow* aWindow, int aButton, int anAction, int aModifiers)
{
	InputManager::GetInstance().OnMouseButtonAction(aButton, anAction, aModifiers);
}

void VulkanRenderSurface::CreateVulkanInstance()
{
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Simpleton Editor";
	appInfo.applicationVersion = VK_MAKE_API_VERSION(0, 0, 0, 1);
	appInfo.pEngineName = "Simpleton";
	appInfo.engineVersion = VK_MAKE_API_VERSION(0, 0, 0, 1);
	appInfo.apiVersion = VK_API_VERSION_1_1;

	VkInstanceCreateInfo instanceCreateInfo = {};
	instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceCreateInfo.pApplicationInfo = &appInfo;
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	instanceCreateInfo.enabledExtensionCount = glfwExtensionCount;
	instanceCreateInfo.ppEnabledExtensionNames = glfwExtensions;
	instanceCreateInfo.enabledLayerCount = 0;

	if (vkCreateInstance(&instanceCreateInfo, nullptr, &myVulkanInstance) != VK_SUCCESS)
	{
		Log::Logger::Print(Log::Severity::Error, Log::Category::Rendering, "Failed to create Vulkan instance");
		glfwTerminate();
		return;
	}
}

VulkanRenderSurface::QueueFamilyIndices VulkanRenderSurface::FindQueueFamilies(VkPhysicalDevice aPhysicalDevice) const
{
	QueueFamilyIndices indices;

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(aPhysicalDevice, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(aPhysicalDevice, &queueFamilyCount, queueFamilies.data());

	for (int index = 0; index < queueFamilies.size(); index++)
	{
		if (queueFamilies[index].queueFlags & VK_QUEUE_GRAPHICS_BIT)
			indices.myGraphicsFamily = index;

		if (indices.isComplete())
			break;
	}

	return indices;
}

bool VulkanRenderSurface::IsDeviceSuitable(VkPhysicalDevice aDevice) const
{
	QueueFamilyIndices indices = FindQueueFamilies(aDevice);

	return indices.isComplete();
}

void VulkanRenderSurface::SetupVulkanPhysicalDevice()
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(myVulkanInstance, &deviceCount, nullptr);

	if (deviceCount == 0)
	{
		Log::Logger::Print(Log::Severity::Error, Log::Category::Rendering, "Failed to find a GPU with Vulkan support");
		glfwTerminate();
		return;
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(myVulkanInstance, &deviceCount, devices.data());

	for (const auto& device : devices)
	{
		if (IsDeviceSuitable(device))
		{
			myVulkanPhysicalDevice = device;
			break;
		}
	}

	if (!myVulkanPhysicalDevice)
	{
		Log::Logger::Print(Log::Severity::Error, Log::Category::Rendering, "Failed to find a GPU with Vulkan support");
		glfwTerminate();
		return;
	}
}
