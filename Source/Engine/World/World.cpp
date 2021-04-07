#include "World.h"

#include "AssetLoader.h"
#include "Camera.h"
#include "../Core/Engine.h"
#include "../Core/EngineContext.h"
#include "../Graphics/Yellowstone.h"
#include "../Core/Logger.h"
#include "../Graphics/Texture.h"
#include "../Graphics/ShaderLibrary.h"
#include "../Graphics/TextureLibrary.h"
#include "EntityFactory.h"

World::World()
{
	myAssetLoader = new AssetLoader();
	myCamera = new Camera();
	myEntityFactory = new EntityFactory();
}

World::~World()
{
}

void World::Update()
{
}

void World::Destroy()
{
	delete myEntityFactory;
	delete myCamera;
	delete myAssetLoader;
	myModels.clear();
}

void World::LoadDummyData()
{
	Model* model = myAssetLoader->LoadModel("../../../Data/Models/Planet/Planet.obj");
	if (!model)
	{
		Log::Logger::Print(Log::Severity::Error, Log::Category::World, "Error loading model from dummy data");
		return;
	}

	for (const std::pair<std::string, TextureType>& texturePair : model->myTextureMap)
	{
		Texture* texture = myAssetLoader->LoadTexture(texturePair.first);
		if (!texture)
		{
			Log::Logger::Print(Log::Severity::Error, Log::Category::World, "Error loading texture from dummy data");
			return;
		}

		texture->myType = texturePair.second;
		TextureLibrary* textureLibrary = Engine::GetInstance().GetContext()->GetSubsystem<Yellowstone>()->GetTextureLibrary();
		if (!textureLibrary)
		{
			Log::Logger::Print(Log::Severity::Error, Log::Category::World, "Error loading texture from dummy data");
			return;
		}

		textureLibrary->CompileTexture(*texture);
		textureLibrary->myTextures.push_back(*texture);
	}

	myModels.push_back(*model);

	Shader* vertexShader = myAssetLoader->LoadShader("../../../Data/Shaders/NormalVertexShader.glsl", ShaderType::Vertex);
	Shader* fragmentShader = myAssetLoader->LoadShader("../../../Data/Shaders/NormalFragmentShader.glsl", ShaderType::Fragment);

	if (!vertexShader || !fragmentShader)
	{
		Log::Logger::Print(Log::Severity::Error, Log::Category::World, "Error loading shaders from dummy data");
		return;
	}

	ShaderLibrary* shaderLibrary = Engine::GetInstance().GetContext()->GetSubsystem<Yellowstone>()->GetShaderLibrary();
	if (!shaderLibrary)
	{
		Log::Logger::Print(Log::Severity::Error, Log::Category::World, "Failed to get Shader Library");
		return;
	}

	shaderLibrary->AddShader(*vertexShader);
	shaderLibrary->AddShader(*fragmentShader);
	shaderLibrary->CompileCurrentShaders();
	shaderLibrary->AttachCurrentShaders();
}

void World::LoadAndAddModel(const std::string& aPath)
{
	Model* model = myAssetLoader->LoadModel(aPath);
	if (!model)
	{
		Log::Logger::Print(Log::Severity::Error, Log::Category::World, "Error loading model from dummy data");
		return;
	}

	for (const std::pair<std::string, TextureType>& texturePair : model->myTextureMap)
	{
		Texture* texture = myAssetLoader->LoadTexture(texturePair.first);
		if (!texture)
		{
			Log::Logger::Print(Log::Severity::Error, Log::Category::World, "Error loading texture from dummy data");
			return;
		}

		texture->myType = texturePair.second;
		TextureLibrary* textureLibrary = Engine::GetInstance().GetContext()->GetSubsystem<Yellowstone>()->GetTextureLibrary();
		if (!textureLibrary)
		{
			Log::Logger::Print(Log::Severity::Error, Log::Category::World, "Error loading texture from dummy data");
			return;
		}

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

	ShaderLibrary* shaderLibrary = Engine::GetInstance().GetContext()->GetSubsystem<Yellowstone>()->GetShaderLibrary();
	if (!shaderLibrary)
	{
		Log::Logger::Print(Log::Severity::Error, Log::Category::World, "Failed to find Shader Library");
		return;
	}

	shaderLibrary->AddShader(*vertexShader);
	shaderLibrary->AddShader(*fragmentShader);
	shaderLibrary->CompileCurrentShaders();
	shaderLibrary->AttachCurrentShaders();
}
