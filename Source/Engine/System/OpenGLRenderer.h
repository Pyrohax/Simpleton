#pragma once

#include "Renderer.h"
#include "../Graphics/GraphicsDefines.h"

class ImguiWrapper;
class RenderContext;
class RenderSurface;

class OpenGLRenderer : public virtual Renderer
{
public:
	OpenGLRenderer();
	~OpenGLRenderer();

	void Initialize() override;
	void CreateAssetBuffers();
	void Update(double aDeltaTime) override;
	void Terminate() override;

	bool HasClosedWindow() const;

private:
	ImguiWrapper* myImguiWrapper;
	RenderContext* myRenderContext;
	RenderSurface* myRenderSurface;
	GraphicsAPI myGraphicsAPI;
	bool myShowConsole;
};
