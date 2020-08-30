#pragma once

class RenderSurface;
class RenderContext;

class Yellowstone
{
public:
	Yellowstone();
	~Yellowstone();

	bool Initialize();
	void Update();
	void Terminate();

	bool HasClosedWindow();

private:
	RenderSurface* myRenderSurface;
	RenderContext* myRenderContext;
};
