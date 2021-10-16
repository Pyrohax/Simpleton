#pragma once

#include <optional>

#include "../RenderSurface.h"

struct GLFWwindow;
struct Texture;
typedef struct VkInstance_T* VkInstance;
typedef struct VkPhysicalDevice_T* VkPhysicalDevice;

class VulkanRenderSurface final : public RenderSurface
{
public:
	VulkanRenderSurface(const GraphicsAPI aGraphicsAPI, const int aWidth, const int aHeight);
	~VulkanRenderSurface();

	void Initialize() override;
	void Tick(double aDeltaTime) override;
	void Destroy() override;

	void SetWindowIcon(const Texture& aTexture) override;

	int GetScreenWidth() const { return myWidth; }
	int GetScreenHeight() const { return myHeight; }
	float GetScreenRatio() const { return myWidth / (float)myHeight; }
	GLFWwindow* GetWindow() const { return myWindow; }
	bool GetShouldClose() const { return myShouldClose; }

protected:
	void PrintDebugInfo() override;

private:
	struct QueueFamilyIndices
	{
		bool isComplete() { return myGraphicsFamily.has_value(); }

		std::optional<uint32_t> myGraphicsFamily;
	};

	static void ErrorCallback(int anError, const char* aDescription);
	static void KeyCallback(GLFWwindow* aWindow, int aKey, int aScancode, int anAction, int aMode);
	static void CursorCallback(GLFWwindow* aWindow, double aXPosition, double aYPosition);
	static void ScrollCallback(GLFWwindow* aWindow, double aXOffset, double aYOffset);
	static void MouseButtonCallback(GLFWwindow* aWindow, int aButton, int anAction, int aModifiers);

	void CreateVulkanInstance();
	void SetupVulkanPhysicalDevice();

	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice aPhysicalDevice) const;
	bool IsDeviceSuitable(VkPhysicalDevice aDevice) const;

private:
	VkInstance myVulkanInstance;
	VkPhysicalDevice myVulkanPhysicalDevice;
};
