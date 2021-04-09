#pragma once

#include "../RenderContext.h"

class OpenGLRenderContext : public RenderContext
{
public:
	OpenGLRenderContext();
	~OpenGLRenderContext();

	void Initialize() override;
	void CreateBuffers(std::vector<Model>& aModels) override;
	void Render(const std::vector<Model>& aModels, const TextureLibrary& aTextureLibrary, ShaderLibrary& aShaderLibrary, Camera& aCamera, const Entity& aLighting, int aWidth, int aHeight, float aDeltaTime) override;
	void Destroy(const std::vector<Model>& aModels) override;

private:
	void PrintDebugInfo() override;
};
