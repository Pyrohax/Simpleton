#pragma once

#include "../../World/Entity.h"
#include "Model.h"

class Camera;
class ShaderLibrary;
class TextureLibrary;

class RenderContext
{
public:
	RenderContext() {}

	virtual void Initialize() = 0;
	virtual void CreateBuffers(std::vector<Model>& aModels) = 0;
	virtual void Render(const std::vector<Model>& aModels, const TextureLibrary& aTextureLibrary, ShaderLibrary& aShaderLibrary, Camera& aCamera, const Entity& aLighting, int aWidth, int aHeight, float aDeltaTime) = 0;
	virtual void Destroy(const std::vector<Model>& aModels) = 0;

private:
	virtual void PrintDebugInfo() = 0;
};
