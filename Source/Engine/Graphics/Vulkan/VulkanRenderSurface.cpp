#include "VulkanRenderSurface.h"

#include "../../Core/InputManager.h"
#include "../../Core/Logger.h"
#include "../Texture.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

const std::vector<const char*> validationLayers =
{
	"VK_LAYER_KHRONOS_validation"
};

VulkanRenderSurface::VulkanRenderSurface(const GraphicsAPI aGraphicsAPI, const int aWidth, const int aHeight)
	: RenderSurface(aGraphicsAPI, aWidth, aHeight)
	, myVulkanInstance(nullptr)
	, myVulkanPhysicalDevice(nullptr)
{}

VulkanRenderSurface::~VulkanRenderSurface()
{}

bool VulkanRenderSurface::Initialize()
{
	glfwSetErrorCallback(ErrorCallback);

	if (!glfwInit())
	{
		Log::Logger::Print(Log::Severity::Error, Log::Category::Rendering, "Failed to initialize GLFW");
		glfwTerminate();
		return false;
	}

	if (!glfwVulkanSupported())
	{
		Log::Logger::Print(Log::Severity::Error, Log::Category::Rendering, "Failed to use Vulkan with GLFW");
		glfwTerminate();
		return false;
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
		return false;
	}

	VkSurfaceKHR vulkanSurface;
	if (glfwCreateWindowSurface(myVulkanInstance, myWindow, nullptr, &vulkanSurface) != VK_SUCCESS)
	{
		Log::Logger::Print(Log::Severity::Error, Log::Category::Rendering, "Failed to open a GLFW window");
		glfwTerminate();
		return false;
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
	return true;
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
	//glfwSwapBuffers(myWindow);
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

bool VulkanRenderSurface::CreateVulkanInstance()
{
	if (myEnableValidationLayers && !CheckValidationLayerSupport())
	{
		Log::Logger::Print(Log::Severity::Error, Log::Category::Rendering, "Validation layers requested but not available!");
		return false;
	}
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
	auto requiredExtensions = GetRequiredExtensions();
	instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
	instanceCreateInfo.ppEnabledExtensionNames = requiredExtensions.data();

	if (myEnableValidationLayers)
	{
		instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		instanceCreateInfo.ppEnabledLayerNames = validationLayers.data();
	}
	else 
		instanceCreateInfo.enabledLayerCount = 0;

	if (vkCreateInstance(&instanceCreateInfo, nullptr, &myVulkanInstance) != VK_SUCCESS)
	{
		Log::Logger::Print(Log::Severity::Error, Log::Category::Rendering, "Failed to create Vulkan instance");
		glfwTerminate();
		return false;
	}
	return true;
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

bool VulkanRenderSurface::SetupVulkanPhysicalDevice()
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(myVulkanInstance, &deviceCount, nullptr);

	if (deviceCount == 0)
	{
		Log::Logger::Print(Log::Severity::Error, Log::Category::Rendering, "Failed to find a GPU with Vulkan support");
		glfwTerminate();
		return false;
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
		return false;
	}
	return true;
}

bool VulkanRenderSurface::CheckValidationLayerSupport() const
{
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const char* layerName : validationLayers)
	{
		bool layerFound = false;

		for (const auto& layerProperties : availableLayers)
		{
			if (strcmp(layerName, layerProperties.layerName) == 0)
			{
				layerFound = true;
				break;
			}
		}

		if (!layerFound)
			return false;
	}
	return true;
}

std::vector<const char*> VulkanRenderSurface::GetRequiredExtensions()
{
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	if (myEnableValidationLayers)
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

	return extensions;
}
