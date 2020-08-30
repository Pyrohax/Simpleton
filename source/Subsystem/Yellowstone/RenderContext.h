#pragma once

#include <glm/mat4x4.hpp>

class ShaderLibrary;
class Camera;
class Model;

class RenderContext
{
public:
	RenderContext();
	~RenderContext();

	void Render(int aWidth, int aHeight);

private:
	void PrintDebugInfo();
	void LoadModel();
	void LoadShaders();
	void CreateCamera();

private:
	ShaderLibrary* myShaderLibrary;
	Camera* myCamera;
	Model* myModel;
};
