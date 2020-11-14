#pragma once

#include "../Model.h"

class Camera;
class ShaderLibrary;
class TextureLibrary;
class Light;

class RenderContext
{
public:
	RenderContext();
	~RenderContext();

	void Initialize();
	void CreateBuffers(std::vector<Model>& aModels);
	void Render(const std::vector<Model>& aModels, const TextureLibrary& aTextureLibrary, ShaderLibrary& aShaderLibrary, int aWidth, int aHeight, float aDeltaTime);
	void Destroy(const std::vector<Model>& aModels);

private:
	void PrintDebugInfo();
	void CreateCamera();
	void CreateLight();

private:
	Camera* myCamera;
	Light* myLight;
};
