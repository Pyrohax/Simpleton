#pragma once

#include "Model.h"

class Camera;
class ShaderLibrary;

class RenderContext
{
public:
	RenderContext();
	~RenderContext();

	void Initialize();
	void CreateBuffers(std::vector<Model>& aModels);
	void Render(const std::vector<Model>& aModels, const ShaderLibrary& aShaderLibrary, int aWidth, int aHeight);
	void Destroy(const std::vector<Model>& aModels);

private:
	void PrintDebugInfo();
	void CreateCamera();

private:
	Camera* myCamera;
};
