#pragma once

#include <GLFW/glfw3.h>

#include <vector>

class Yellowstone
{
public:
	Yellowstone();
	~Yellowstone();

	bool Init();

	void CreatePlateau();
	void SetupDebugMessenger();
	void CheckExtensions();
	void PollEvents();
	void Terminate();

	bool CheckValidationLayerSupport();
	bool HasClosedWindow();

	GLFWwindow* GetWindow() { return myWindow; }
	std::vector<const char*> GetRequiredExtensions();

private:
	GLFWwindow* myWindow;
	VkInstance myVulkanInstance;
	VkDebugUtilsMessengerEXT myDebugMessenger;
	std::vector<const char*> myValidationLayers;
};
