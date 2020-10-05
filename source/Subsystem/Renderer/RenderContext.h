#pragma once

#include "Model.h"

class Camera;
class ShaderLibrary;
class TextureLibrary;

class RenderContext
{
public:
	RenderContext();
	~RenderContext();

	void Initialize();
	void CreateBuffers(std::vector<Model>& aModels);
	void Render(const std::vector<Model>& aModels, const TextureLibrary& aTextureLibrary, const ShaderLibrary& aShaderLibrary, int aWidth, int aHeight, double aDeltaTime);
	void Destroy(const std::vector<Model>& aModels);

private:
	void PrintDebugInfo();
	void CreateCamera();

private:
	Camera* myCamera;
};
