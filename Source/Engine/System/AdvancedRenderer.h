#pragma once

#include "Renderer.h"
#include "../Graphics/GraphicsDefines.h"

class AdvancedRenderer : public virtual Renderer
{
public:
	AdvancedRenderer();
	~AdvancedRenderer();

	void Initialize() override;
	void Update(double aDeltaTime) override;
	void Terminate() override;
private:
	GraphicsAPI myGrahpicsAPI;
};

AdvancedRenderer::AdvancedRenderer()
	: myGrahpicsAPI(GraphicsAPI::None)
{
}

AdvancedRenderer::~AdvancedRenderer()
{
}

inline void AdvancedRenderer::Initialize()
{
}
