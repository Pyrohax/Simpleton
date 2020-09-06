#include "Yellowstone.h"

#include <iostream>


Yellowstone::Yellowstone()
	: myWindow(nullptr)
{

}

Yellowstone::~Yellowstone()
{
}

bool Yellowstone::Init()
{
	CreatePlateau();
	CheckExtensions();
	return true;
}

bool Yellowstone::CheckValidationLayerSupport()
{
	return true;
}

std::vector<const char*> Yellowstone::GetRequiredExtensions()
{
	std::vector<const char*> extensions;

	return extensions;
}

bool Yellowstone::HasClosedWindow()
{
	return glfwWindowShouldClose(myWindow);
}

void Yellowstone::PollEvents()
{
	glfwPollEvents();
}
void Yellowstone::CreatePlateau()
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	myWindow = glfwCreateWindow(1280, 720, "Yellowstone", nullptr, nullptr);

	SetupDebugMessenger();
}

void Yellowstone::SetupDebugMessenger()
{
}

void Yellowstone::CheckExtensions()
{
	
}

void Yellowstone::Terminate()
{
	glfwDestroyWindow(myWindow);
	glfwTerminate();
}
