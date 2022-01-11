#include "Yellowstone.h"

#include "../Core/ECS/CameraComponent.h"
#include "../Core/ECS/Entity.h"
#include "../Core/Engine.h"
#include "../Graphics/OpenGL/OpenGLRenderContext.h"
#include "../Graphics/OpenGL/OpenGLRenderSurface.h"
#include "../Graphics/OpenGL/OpenGLShaderLibrary.h"
#include "../Graphics/OpenGL/OpenGLTextureLibrary.h"
#include "../Graphics/RenderSurface.h"
#include "../Graphics/UI/ImguiWrapper.h"
#include "../Graphics/Vulkan/VulkanRenderSurface.h"
#include "../Graphics/Vulkan/VulkanShaderLibrary.h"
#include "../World/AssetLoader.h"
#include "../World/World.h"

Yellowstone::Yellowstone(EngineContext* aContext)
	: Subsystem(aContext)
	, myGraphicsAPI(GraphicsAPI::Vulkan)
	, myRenderSurface(nullptr)
	, myRenderContext(nullptr)
	, myShaderLibrary(nullptr)
	, myTextureLibrary(nullptr)
	, myImguiWrapper(nullptr)
{
	switch (myGraphicsAPI)
	{
		case GraphicsAPI::None:
		case GraphicsAPI::DirectX12:
		{
			break;
		}
		case GraphicsAPI::OpenGL:
		{
			myRenderSurface = new OpenGLRenderSurface(1280, 720);
			myRenderContext = new OpenGLRenderContext();
			myShaderLibrary = new OpenGLShaderLibrary();
			myTextureLibrary = new OpenGLTextureLibrary();
			myImguiWrapper = new UI::ImguiWrapper();
			break;
		}
		case GraphicsAPI::Vulkan:
		{
			myRenderSurface = new VulkanRenderSurface(1280, 720);
			myShaderLibrary = new VulkanShaderLibrary();
			break;
		}
	}
}

Yellowstone::~Yellowstone()
{
	delete myImguiWrapper;
	delete myTextureLibrary;
	delete myShaderLibrary;
	delete myRenderContext;
	delete myRenderSurface;
}

void Yellowstone::Initialize()
{
	if (myRenderSurface)
	{
		if (!myRenderSurface->Initialize())
			Log::Logger::Print(Log::Severity::Error, Log::Category::Rendering, "Failed to initialize Render Surface");
	}

	if (myRenderContext)
		myRenderContext->Initialize();

	const Engine& engine = Engine::GetInstance();
	World& world = engine.GetWorld();

	if (Texture* icon = world.GetAssetLoader().LoadTexture("../../../Data/Icons/Editor.png"))
	{
		myRenderSurface->SetWindowIcon(*icon);
		free(icon);
	}

	myShaderLibrary->CreateProgram();

	if (myImguiWrapper && myRenderSurface)
		myImguiWrapper->Initialize(myRenderSurface->GetWindow());
}

void Yellowstone::Update(const float aDeltaTime)
{
	Engine& engine = Engine::GetInstance();
	World& world = engine.GetWorld();

	if (!world.GetModels().empty())
		myShaderLibrary->BindShaders();

	if (myRenderContext)
	{
		myImguiWrapper->CreateFrame();
		myImguiWrapper->Render();
		auto& cameraComponent = world.GetCamera().GetComponent<CameraComponent>();
		cameraComponent.Update(aDeltaTime);
		auto& lightingComponent = world.GetLighting().GetComponent<LightingComponent>();
		auto& lightingTransformComponent = world.GetLighting().GetComponent<TransformComponent>();
		myRenderContext->Render(world.GetModels(), *myTextureLibrary, *myShaderLibrary, cameraComponent, lightingComponent, lightingTransformComponent, myRenderSurface->GetScreenWidth(), myRenderSurface->GetScreenHeight(), aDeltaTime);
		myImguiWrapper->Draw();
	}

	myRenderSurface->Tick(aDeltaTime);

	if (HasClosedWindow())
		engine.SetShouldShutdown(true);
}

void Yellowstone::Terminate()
{
	const Engine& engine = Engine::GetInstance();
	const World& world = engine.GetWorld();
	if (myRenderContext)
		myRenderContext->Destroy(world.GetModels());

	myRenderSurface->Destroy();

	if (myImguiWrapper)
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
