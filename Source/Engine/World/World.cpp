#include "World.h"

#include "../Core/Engine.h"
#include "../Core/EngineContext.h"
#include "../Core/Logger.h"
#include "../ECS/Core/Coordinator.h"
#include "../Graphics/ShaderLibrary.h"
#include "../Graphics/Texture.h"
#include "../Graphics/TextureLibrary.h"
#include "../Graphics/Yellowstone.h"
#include "AssetLoader.h"
#include "CameraComponent.h"
#include "LightingComponent.h"
#include "TransformComponent.h"
#include "../ECS/Core/Entity.h"

World::World(Coordinator* aCoordinator)
{
	myAssetLoader = std::make_unique<AssetLoader>();
	myLighting = aCoordinator->CreateEntity();
	myCamera = aCoordinator->CreateEntity();
}

World::~World()
{
	delete myCamera;
	delete myLighting;
	myAssetLoader.reset();
}

void World::Initialize()
{
	LightingComponent* lightingComponent = new LightingComponent();
	myLighting->AddComponent<LightingComponent>(*lightingComponent);

	TransformComponent* transformComponent = new TransformComponent(glm::vec3(-5.f, -2.5f, 7.5f));
	myLighting->AddComponent<TransformComponent>(*transformComponent);

	CameraComponent* cameraComponent = new CameraComponent();
	myCamera->AddComponent<CameraComponent>(*cameraComponent);
}

void World::LoadDefaultData()
{
	LoadAndAddShaders("../../../Data/Shaders/DefaultVertexShader.glsl", "../../../Data/Shaders/DefaultFragmentShader.glsl");
}

void World::LoadAndAddModel(const std::string& aPath)
{
	Model* model = myAssetLoader->LoadModel(aPath);
	if (!model)
	{
		Log::Logger::Print(Log::Severity::Error, Log::Category::World, "Error loading model %s", aPath.c_str());
		return;
	}

	TextureLibrary* textureLibrary = Engine::GetInstance().GetContext().GetSubsystem<Yellowstone>()->GetTextureLibrary();
	if (!textureLibrary)
	{
		Log::Logger::Print(Log::Severity::Error, Log::Category::World, "Failed to access Texture Library");
		return;
	}

	for (const std::pair<std::string, TextureType>& texturePair : model->myTextureMap)
	{
		Texture* texture = myAssetLoader->LoadTexture(texturePair.first);
		if (!texture)
		{
			Log::Logger::Print(Log::Severity::Error, Log::Category::World, "Error loading texture %s", texturePair.first.c_str());
			return;
		}

		texture->myType = texturePair.second;

		textureLibrary->CompileTexture(*texture);
		textureLibrary->myTextures.push_back(*texture);
	}

	myModels.push_back(*model);
}

void World::LoadAndAddShaders(const std::string& aVertexShaderPath, const std::string& aFragmentShaderPath)
{
	Shader* vertexShader = myAssetLoader->LoadShader(aVertexShaderPath, ShaderType::Vertex);
	Shader* fragmentShader = myAssetLoader->LoadShader(aFragmentShaderPath, ShaderType::Fragment);

	if (!vertexShader || !fragmentShader)
	{
		Log::Logger::Print(Log::Severity::Error, Log::Category::World, "Error loading shaders %s %s", aVertexShaderPath.c_str(), aFragmentShaderPath.c_str());
		return;
	}

	ShaderLibrary* shaderLibrary = Engine::GetInstance().GetContext().GetSubsystem<Yellowstone>()->GetShaderLibrary();
	if (!shaderLibrary)
	{
		Log::Logger::Print(Log::Severity::Error, Log::Category::World, "Failed to access Shader Library");
		return;
	}

	shaderLibrary->AddShader(*vertexShader);
	shaderLibrary->AddShader(*fragmentShader);
	shaderLibrary->CompileCurrentShaders();
	shaderLibrary->AttachCurrentShaders();
}
