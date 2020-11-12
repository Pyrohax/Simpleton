#include "OpenGLRenderer.h"

#include "../Engine.h"
#include "../World/World.h"
#include "../World/AssetLoader.h"
#include "../Graphics/OpenGL/ImguiWrapper.h"
#include "../Graphics/OpenGL/RenderContext.h"
#include "../Graphics/OpenGL/RenderSurface.h"
#include "../Graphics/OpenGL/ShaderLibrary.h"

OpenGLRenderer::OpenGLRenderer()
	: myImguiWrapper(nullptr)
	, myRenderContext(nullptr)
	, myRenderSurface(nullptr)
	, myGraphicsAPI(GraphicsAPI::None)
	, myShowConsole(true)
{
	myRenderSurface = new RenderSurface();
	myRenderContext = new RenderContext();
	myImguiWrapper = new ImguiWrapper();
}

OpenGLRenderer::~OpenGLRenderer()
{
	delete myRenderContext;
	delete myRenderSurface;
	delete myImguiWrapper;
}

void OpenGLRenderer::Initialize()
{
	myRenderSurface->Initialize();
	myRenderContext->Initialize();
	Engine& engine = Engine::GetInstance();
	World& world = *engine.GetWorld();

	if (Texture* icon = world.GetAssetLoader().LoadTexture("../../../Data/Icons/Editor.png"))
	{
		myRenderSurface->SetWindowIcon(*icon);
		free(icon);
	}
}

void OpenGLRenderer::CreateAssetBuffers()
{
	Engine& engine = Engine::GetInstance();
	World& world = *engine.GetWorld();
	myRenderContext->CreateBuffers(world.myModels);
	myImguiWrapper->Initialize(myRenderSurface->GetWindow());
}

void OpenGLRenderer::Update(double aDeltaTime)
{
	Engine& engine = Engine::GetInstance();
	World& world = *engine.GetWorld();
	world.GetShaderLibrary().BindShaders();
	myImguiWrapper->CreateFrame();
	myImguiWrapper->Render(aDeltaTime);
	myRenderContext->Render(world.myModels, world.GetTextureLibrary(), world.GetShaderLibrary(), myRenderSurface->GetScreenWidth(), myRenderSurface->GetScreenHeight(), aDeltaTime);
	myImguiWrapper->Draw();
	myRenderSurface->Tick(aDeltaTime);
}

void OpenGLRenderer::Terminate()
{
	Engine& engine = Engine::GetInstance();
	World& world = *engine.GetWorld();
	myRenderContext->Destroy(world.myModels);
	myRenderSurface->Destroy();
	myImguiWrapper->Destroy();
}

bool OpenGLRenderer::HasClosedWindow() const
{
	return myRenderSurface->GetShouldClose();
}
