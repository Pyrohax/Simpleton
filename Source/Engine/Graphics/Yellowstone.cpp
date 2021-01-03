#include "Yellowstone.h"

#include "../Core/Engine.h"
#include "../World/World.h"
#include "../World/AssetLoader.h"
#include "../Graphics/UI/ImguiWrapper.h"
#include "../Graphics/RenderSurface.h"
#include "../Graphics/OpenGL/OpenGLRenderContext.h"
#include "../Graphics/OpenGL/OpenGLShaderLibrary.h"

Yellowstone::Yellowstone(EngineContext* aContext) : Subsystem(aContext)
{
	myRenderSurface = new RenderSurface();
	myRenderContext = new OpenGLRenderContext();
	myImguiWrapper = new UI::ImguiWrapper();
	myGraphicsAPI = GraphicsAPI::OpenGL;
	myShowConsole = true;
}

Yellowstone::~Yellowstone()
{
	delete myRenderContext;
	delete myRenderSurface;
	delete myImguiWrapper;
}

void Yellowstone::Initialize()
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

void Yellowstone::CreateAssetBuffers()
{
	Engine& engine = Engine::GetInstance();
	World& world = *engine.GetWorld();
	myRenderContext->CreateBuffers(world.myModels);
	myImguiWrapper->Initialize(myRenderSurface->GetWindow());
}

void Yellowstone::Update(float aDeltaTime)
{
	Engine& engine = Engine::GetInstance();
	World& world = *engine.GetWorld();

	if (world.myModels.size() > 0)
	{
		world.GetShaderLibrary().BindShaders();
	}

	myImguiWrapper->CreateFrame();
	myImguiWrapper->Render(aDeltaTime);
	myRenderContext->Render(world.myModels, world.GetTextureLibrary(), world.GetShaderLibrary(), world.GetCamera(), myRenderSurface->GetScreenWidth(), myRenderSurface->GetScreenHeight(), aDeltaTime);
	myImguiWrapper->Draw();
	myRenderSurface->Tick(aDeltaTime);

	if (HasClosedWindow())
	{
		engine.SetShouldShutdown(true);
	}
}

void Yellowstone::Terminate()
{
	Engine& engine = Engine::GetInstance();
	World& world = *engine.GetWorld();
	myRenderContext->Destroy(world.myModels);
	myRenderSurface->Destroy();
	myImguiWrapper->Destroy();
}

bool Yellowstone::HasClosedWindow() const
{
	return myRenderSurface->GetShouldClose();
}
