#include "Renderer.h"

#include "RenderContext.h"
#include "RenderSurface.h"
#include "World.h"
#include "ShaderLibrary.h"
#include "ImguiWrapper.h"

Renderer::Renderer()
	: myRenderContext(nullptr)
	, myRenderSurface(nullptr)
	, myImguiWrapper(nullptr)
{
	myRenderSurface = new RenderSurface();
	myRenderContext = new RenderContext();
	myWorld = new World();
	myImguiWrapper = new ImguiWrapper();
}

Renderer::~Renderer()
{
	delete myRenderContext;
	delete myRenderSurface;
	delete myWorld;
	delete myImguiWrapper;
}

bool Renderer::Initialize()
{
	myWorld->LoadDummyData();
	myRenderContext->CreateBuffers(myWorld->myModels);
	myImguiWrapper->Initialize(myRenderSurface->GetWindow());

	return true;
}

void Renderer::Update()
{
	myWorld->GetShaderLibrary().BindShaders();
	myImguiWrapper->CreateFrame();
	myImguiWrapper->Render();
	myRenderContext->Render(myWorld->myModels, myWorld->GetShaderLibrary(), myRenderSurface->GetScreenWidth(), myRenderSurface->GetScreenHeight());
	myImguiWrapper->Draw();
	myRenderSurface->Tick();
}

void Renderer::Terminate()
{
	myRenderContext->Destroy(myWorld->myModels);
	myRenderSurface->Destroy();
	myImguiWrapper->Destroy();
	myWorld->Destroy();
}

bool Renderer::HasClosedWindow()
{
	return myRenderSurface->myShouldClose;
}
