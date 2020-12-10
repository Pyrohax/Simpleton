#pragma once

#include "../Core/Subsystem.h"
#include "../Graphics/GraphicsDefines.h"

namespace UI
{
	class ImguiWrapper;
}

class EngineContext;
class RenderContext;
class RenderSurface;

class Yellowstone : public Subsystem
{
public:
	Yellowstone(EngineContext* aContext);
	~Yellowstone();

	void Initialize() override;
	void Update(float aDeltaTime) override;
	void Terminate() override;

	void CreateAssetBuffers();

	bool HasClosedWindow() const;

private:
	UI::ImguiWrapper* myImguiWrapper;
	RenderContext* myRenderContext;
	RenderSurface* myRenderSurface;
	GraphicsAPI myGraphicsAPI;
	bool myShowConsole;
};
