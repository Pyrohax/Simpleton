#include "Yellowstone.h"

#include "../Core/Engine.h"
#include "../Graphics/OpenGL/OpenGLRenderContext.h"
#include "../Graphics/OpenGL/OpenGLRenderSurface.h"
#include "../Graphics/OpenGL/OpenGLShaderLibrary.h"
#include "../Graphics/OpenGL/OpenGLTextureLibrary.h"
#include "../Graphics/RenderSurface.h"
#include "../Graphics/UI/ImguiWrapper.h"
#include "../Graphics/Vulkan/VulkanRenderSurface.h"
#include "../World/AssetLoader.h"
#include "../World/CameraComponent.h"
#include "../World/World.h"

Yellowstone::Yellowstone(EngineContext* aContext)
	: Subsystem(aContext)
	, myGraphicsAPI(GraphicsAPI::Vulkan)
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
			break;
		}
		case GraphicsAPI::DirectX12:
		{
			myShowConsole = true;
			break;
		}
		case GraphicsAPI::OpenGL:
		{
			myRenderSurface = new OpenGLRenderSurface(1280, 720);
			myRenderContext = new OpenGLRenderContext();
			myShaderLibrary = new OpenGLShaderLibrary();
			myTextureLibrary = new OpenGLTextureLibrary();
			myImguiWrapper = new UI::ImguiWrapper();
			myShowConsole = true;
			break;
		}
		case GraphicsAPI::Vulkan:
		{
			myRenderSurface = new VulkanRenderSurface(1280, 720);
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
	if (myRenderSurface)
		myRenderSurface->Initialize();

	if (myRenderContext)
		myRenderContext->Initialize();

	Engine& engine = Engine::GetInstance();
	World& world = engine.GetWorld();

	if (Texture* icon = world.GetAssetLoader().LoadTexture("../../../Data/Icons/Editor.png"))
	{
		myRenderSurface->SetWindowIcon(*icon);
		free(icon);
	}

	if (myGraphicsAPI == GraphicsAPI::OpenGL)
		myShaderLibrary->CreateProgram();

	if (myImguiWrapper && myRenderSurface)
		myImguiWrapper->Initialize(myRenderSurface->GetWindow());
}

void Yellowstone::Update(float aDeltaTime)
{
	Engine& engine = Engine::GetInstance();
	World& world = engine.GetWorld();

	if (world.GetModels().size() > 0)
		myShaderLibrary->BindShaders();

	if (myRenderContext)
	{
		myImguiWrapper->CreateFrame();
		myImguiWrapper->Render(aDeltaTime);
		CameraComponent& cameraComponent = world.GetCamera().GetComponent<CameraComponent>();
		cameraComponent.Update(aDeltaTime);
		LightingComponent& lightingComponent = world.GetLighting().GetComponent<LightingComponent>();
		TransformComponent& lightingTransformComponent = world.GetLighting().GetComponent<TransformComponent>();
		myRenderContext->Render(world.GetModels(), *myTextureLibrary, *myShaderLibrary, cameraComponent, lightingComponent, lightingTransformComponent, myRenderSurface->GetScreenWidth(), myRenderSurface->GetScreenHeight(), aDeltaTime);
		myImguiWrapper->Draw();
	}

	myRenderSurface->Tick(aDeltaTime);

	if (HasClosedWindow())
		engine.SetShouldShutdown(true);
}

void Yellowstone::Terminate()
{
	Engine& engine = Engine::GetInstance();
	World& world = engine.GetWorld();
	myRenderContext->Destroy(world.GetModels());
	myRenderSurface->Destroy();
	myImguiWrapper->Destroy();
}

void Yellowstone::CreateAssetBuffers(std::vector<Model>& aModels)
{
	if (myRenderContext)
		myRenderContext->CreateBuffers(aModels);
}

bool Yellowstone::HasClosedWindow() const
{
	return myRenderSurface->GetShouldClose();
}
