#pragma once

class RenderContext;
class RenderSurface;
class World;
class ImguiWrapper;

class Renderer
{
public:
	Renderer();
	~Renderer();

	bool Initialize();
	void Update();
	void Terminate();

	bool HasClosedWindow();

private:
	RenderContext* myRenderContext;
	RenderSurface* myRenderSurface;
	World* myWorld;
	ImguiWrapper* myImguiWrapper;
};
