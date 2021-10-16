#pragma once

#include "../RenderContext.h"

class OpenGLRenderContext final : public RenderContext
{
public:
	OpenGLRenderContext();
	~OpenGLRenderContext();

	void Initialize() override;
	void CreateBuffers(std::vector<Model>& aModels) override;
	void Render(const std::vector<Model>& aModels, const TextureLibrary& aTextureLibrary, ShaderLibrary& aShaderLibrary, CameraComponent& aCameraComponent, LightingComponent& aLightingComponent, TransformComponent& aTransformComponentLighting, int aWidth, int aHeight, float aDeltaTime) override;
	void Destroy(const std::vector<Model>& aModels) override;

private:
	void PrintDebugInfo() override;
};
