#pragma once

#include "../RenderSurface.h"

#include <optional>
#include <vector>
#include <vulkan/vulkan.hpp>

struct GLFWwindow;
struct Texture;
typedef struct VkInstance_T* VkInstance;
typedef struct VkPhysicalDevice_T* VkPhysicalDevice;

class VulkanRenderSurface final : public RenderSurface
{
public:
	VulkanRenderSurface(const int aWidth, const int aHeight);
	~VulkanRenderSurface();

	bool Initialize() override;
	void Tick(double aDeltaTime) override;
	void Destroy() override;

	void SetWindowIcon(const Texture& aTexture) override;

	int GetScreenWidth() const { return myWidth; }
	int GetScreenHeight() const { return myHeight; }
	float GetScreenRatio() const { return myWidth / static_cast<float>(myHeight); }
	GLFWwindow* GetWindow() const { return myWindow; }
	bool GetShouldClose() const { return myShouldClose; }

protected:
	void PrintDebugInfo() override;

private:
	struct QueueFamilyIndices
	{
		bool IsComplete() { return myGraphicsFamily.has_value(); }

		std::optional<uint32_t> myGraphicsFamily;
	};

	static void ErrorCallback(int anError, const char* aDescription);
	static void KeyCallback(GLFWwindow* aWindow, int aKey, int aScancode, int anAction, int aMode);
	static void CursorCallback(GLFWwindow* aWindow, double aXPosition, double aYPosition);
	static void ScrollCallback(GLFWwindow* aWindow, double aXOffset, double aYOffset);
	static void MouseButtonCallback(GLFWwindow* aWindow, int aButton, int anAction, int aModifiers);

	bool CreateVulkanInstance();
	bool SetupVulkanPhysicalDevice();
	void SetupDebugMessenger();

	bool CheckValidationLayerSupport() const;
	std::vector<const char*> GetRequiredExtensions();
	void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& aCreateInfo) const;
	VkResult CreateDebugUtilsMessengerEXT(VkInstance aInstance, const VkDebugUtilsMessengerCreateInfoEXT* aCreateInfo, const VkAllocationCallbacks* aAllocator, VkDebugUtilsMessengerEXT* aDebugMessenger);
	void DestroyDebugUtilMessengerEXT(VkInstance aInstance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* aAllocator);

	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice aPhysicalDevice) const;
	bool IsDeviceSuitable(VkPhysicalDevice aDevice) const;

	static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT aMessageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT aMessageType,
		const VkDebugUtilsMessengerCallbackDataEXT* aCallbackData,
		void* aUserData);

private:
	VkInstance myVulkanInstance;
	VkPhysicalDevice myVulkanPhysicalDevice;
	VkDebugUtilsMessengerEXT myDebugMessenger;
};
