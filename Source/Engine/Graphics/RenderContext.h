#pragma once

#include "Model.h"

#include "../Core/ECS/CameraComponent.h"
#include "../Core/ECS/LightingComponent.h"
#include "../Core/ECS/TransformComponent.h"

class ShaderLibrary;
class TextureLibrary;

class RenderContext
{
public:
	RenderContext() {}

	virtual void Initialize() = 0;
	virtual void CreateBuffers(std::vector<Model>& aModels) = 0;
	virtual void Render(const std::vector<Model>& aModels, const TextureLibrary& aTextureLibrary, ShaderLibrary& aShaderLibrary, CameraComponent& aCameraComponent, LightingComponent& aLightingComponent, TransformComponent& aTransformComponentLighting,  int aWidth, int aHeight, float aDeltaTime) = 0;
	virtual void Destroy(const std::vector<Model>& aModels) = 0;

private:
	virtual void PrintDebugInfo() = 0;
};
