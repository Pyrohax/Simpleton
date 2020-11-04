#include "Renderer.h"

#include "RenderContext.h"
#include "RenderSurface.h"
#include "World.h"
#include "ShaderLibrary.h"
#include "ImguiWrapper.h"
#include "AssetLoader.h"

Renderer::Renderer()
	: myRenderContext(nullptr)
	, myRenderSurface(nullptr)
	, myImguiWrapper(nullptr)
	, myShowConsole(true)
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
	myRenderSurface->Initialize();
	myRenderContext->Initialize();
	myWorld->LoadDummyData();
	myRenderContext->CreateBuffers(myWorld->myModels);
	myImguiWrapper->Initialize(myRenderSurface->GetWindow());

	if (Texture* icon = myWorld->GetAssetLoader().LoadTexture("../Data/Icons/Editor.png"))
	{
		myRenderSurface->SetWindowIcon(*icon);
		free(icon);
	}

	return true;
}

void Renderer::Update(double aDeltaTime)
{
	myWorld->GetShaderLibrary().BindShaders();
	myImguiWrapper->CreateFrame();
	myImguiWrapper->Render(aDeltaTime);
	myRenderContext->Render(myWorld->myModels, myWorld->GetTextureLibrary(), myWorld->GetShaderLibrary(), myRenderSurface->GetScreenWidth(), myRenderSurface->GetScreenHeight(), aDeltaTime);
	myImguiWrapper->Draw();
	myRenderSurface->Tick(aDeltaTime);
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
	return myRenderSurface->GetShouldClose();
}
