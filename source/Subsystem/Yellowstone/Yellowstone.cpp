#include "Yellowstone.h"
#include "RenderSurface.h"
#include "RenderContext.h"

Yellowstone::Yellowstone()
	: myRenderSurface(nullptr)
	, myRenderContext(nullptr)
{
	myRenderSurface = new RenderSurface();
	myRenderContext = new RenderContext();
}

Yellowstone::~Yellowstone()
{
}

bool Yellowstone::Initialize()
{
	return true;
}

void Yellowstone::Update()
{
	myRenderContext->Render(myRenderSurface->GetScreenWidth(), myRenderSurface->GetScreenHeight());
	myRenderSurface->Tick();
}

void Yellowstone::Terminate()
{
	myRenderSurface->Destroy();
}

bool Yellowstone::HasClosedWindow()
{
	return myRenderSurface->myShouldClose;
}
