#pragma once

#include "Model.h"

class Camera;
class ShaderLibrary;
class TextureLibrary;
class Light;

class RenderContext
{
public:
	RenderContext() {}

	virtual void Initialize() = 0;
	virtual void CreateBuffers(std::vector<Model>& aModels) = 0;
	virtual void Render(const std::vector<Model>& aModels, const TextureLibrary& aTextureLibrary, ShaderLibrary& aShaderLibrary, Camera& aCamera, int aWidth, int aHeight, float aDeltaTime) = 0;
	virtual void Destroy(const std::vector<Model>& aModels) = 0;

private:
	virtual void PrintDebugInfo() = 0;
	virtual void CreateLight() = 0;
};
