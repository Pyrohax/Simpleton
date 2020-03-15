#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

void Test()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Yellowstone", nullptr, nullptr);
}