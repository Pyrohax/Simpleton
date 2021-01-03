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
class ShaderLibrary;
class TextureLibrary;

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

	ShaderLibrary* GetShaderLibrary() { return myShaderLibrary; }
	TextureLibrary* GetTextureLibrary() { return myTextureLibrary; }

	GraphicsAPI GetGraphicsAPI() const { return myGraphicsAPI; }

private:
	UI::ImguiWrapper* myImguiWrapper;
	RenderContext* myRenderContext;
	RenderSurface* myRenderSurface;
	ShaderLibrary* myShaderLibrary;
	TextureLibrary* myTextureLibrary;
	GraphicsAPI myGraphicsAPI;
	bool myShowConsole;
};
