#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>

class Yellowstone
{
public:
	Yellowstone();
	~Yellowstone();

	bool CheckValidationLayerSupport();
	std::vector<const char*> GetRequiredExtensions();

	void CreatePlateau();
	void SetupDebugMessenger();
	void CheckExtensions();
	void Shutdown();

	GLFWwindow* GetWindow() { return myWindow; }

private:
	GLFWwindow* myWindow;
	VkInstance myVulkanInstance;
	VkDebugUtilsMessengerEXT myDebugMessenger;
	std::vector<const char*> myValidationLayers;
};