#include "Yellowstone.h"

#include "../Core/Engine.h"
#include "../World/World.h"
#include "../World/AssetLoader.h"
#include "../Graphics/UI/ImguiWrapper.h"
#include "../Graphics/RenderSurface.h"
#include "../Graphics/OpenGL/OpenGLRenderContext.h"
#include "../Graphics/OpenGL/OpenGLTextureLibrary.h"
#include "../Graphics/OpenGL/OpenGLShaderLibrary.h"

Yellowstone::Yellowstone(EngineContext* aContext)
	: Subsystem(aContext)
	, myGraphicsAPI(GraphicsAPI::OpenGL)
	, myRenderSurface(nullptr)
	, myRenderContext(nullptr)
	, myShaderLibrary(nullptr)
	, myTextureLibrary(nullptr)
	, myImguiWrapper(nullptr)
	, myShowConsole(false)
{
	switch (myGraphicsAPI)
	{
		case GraphicsAPI::None:
		{
			myRenderSurface = new RenderSurface();
			break;
		}
		case GraphicsAPI::DirectX12:
		{
			myRenderSurface = new RenderSurface();
			myShowConsole = true;
			break;
		}
		case GraphicsAPI::OpenGL:
		{
			myRenderSurface = new RenderSurface();
			myRenderContext = new OpenGLRenderContext();
			myShaderLibrary = new OpenGLShaderLibrary();
			myTextureLibrary = new OpenGLTextureLibrary();
			myImguiWrapper = new UI::ImguiWrapper();
			myShowConsole = true;
			break;
		}
		case GraphicsAPI::Vulkan:
		{
			myRenderSurface = new RenderSurface();
			myShowConsole = true;
			break;
		}
	}
}

Yellowstone::~Yellowstone()
{
	delete myRenderContext;
	delete myRenderSurface;
	delete myShaderLibrary;
	delete myTextureLibrary;
	delete myImguiWrapper;
}

void Yellowstone::Initialize()
{
	myRenderSurface->Initialize(myGraphicsAPI);

	if (myRenderContext)
	{
		myRenderContext->Initialize();
	}

	Engine& engine = Engine::GetInstance();
	World& world = *engine.GetWorld();

	if (Texture* icon = world.GetAssetLoader().LoadTexture("../../../Data/Icons/Editor.png"))
	{
		myRenderSurface->SetWindowIcon(*icon);
		free(icon);
	}

	if (myGraphicsAPI == GraphicsAPI::OpenGL)
	{
		myShaderLibrary->CreateProgram();
	}
}

void Yellowstone::CreateAssetBuffers()
{
	Engine& engine = Engine::GetInstance();
	World& world = *engine.GetWorld();

	if (myRenderContext)
	{
		myRenderContext->CreateBuffers(world.myModels);
	}

	if (myImguiWrapper)
	{
		myImguiWrapper->Initialize(myRenderSurface->GetWindow());
	}
}

void Yellowstone::Update(float aDeltaTime)
{
	Engine& engine = Engine::GetInstance();
	World& world = *engine.GetWorld();

	if (world.myModels.size() > 0)
	{
		myShaderLibrary->BindShaders();
	}

	if (myRenderContext)
	{
		myImguiWrapper->CreateFrame();
		myImguiWrapper->Render(aDeltaTime);
		myRenderContext->Render(world.myModels, *myTextureLibrary, *myShaderLibrary, world.GetCamera(), myRenderSurface->GetScreenWidth(), myRenderSurface->GetScreenHeight(), aDeltaTime);
		myImguiWrapper->Draw();
	}

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
