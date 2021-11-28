#pragma once

#include "../Core/Subsystem.h"
#include "../Graphics/GraphicsDefines.h"
#include "../Graphics/Model.h"

namespace UI
{
	class ImguiWrapper;
}

class EngineContext;
class RenderContext;
class RenderSurface;
class ShaderLibrary;
class TextureLibrary;

class Yellowstone final : public Subsystem
{
public:
	Yellowstone(EngineContext* aContext);
	~Yellowstone() override;

	void Initialize() override;
	void Update(float aDeltaTime) override;
	void Terminate() override;

	void CreateAssetBuffers(std::vector<Model>& aModels);

	bool HasClosedWindow() const;

	ShaderLibrary* GetShaderLibrary() { return myShaderLibrary; }
	TextureLibrary* GetTextureLibrary() { return myTextureLibrary; }

	GraphicsAPI GetGraphicsAPI() const { return myGraphicsAPI; }
	UI::ImguiWrapper* GetImguiWrapper() const { return myImguiWrapper; }

private:
	UI::ImguiWrapper* myImguiWrapper;
	RenderContext* myRenderContext;
	RenderSurface* myRenderSurface;
	ShaderLibrary* myShaderLibrary;
	TextureLibrary* myTextureLibrary;
	GraphicsAPI myGraphicsAPI;
	bool myShowConsole;
};
