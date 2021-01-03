#include "World.h"

#include "AssetLoader.h"
#include "Camera.h"
#include "../Core/Logger.h"
#include "../Graphics/Texture.h"
#include "../Graphics/OpenGL/OpenGLShaderLibrary.h"
#include "../Graphics/OpenGL/OpenGLTextureLibrary.h"

World::World()
{
	myAssetLoader = new AssetLoader();
	myShaderLibrary = new OpenGLShaderLibrary();
	myTextureLibrary = new OpenGLTextureLibrary();
	myCamera = new Camera();
}

World::~World()
{
}

void World::LoadDummyData()
{
	myShaderLibrary->CreateProgram();

	Model* model = myAssetLoader->LoadModel("../../../Data/Models/Planet/Planet.obj");
	if (!model)
	{
		Log::Logger::Print(Log::Severity::Error, Log::Category::World, "Error loading dummy data");
		return;
	}

	for (const std::pair<std::string, TextureType>& texturePair : model->myTextureMap)
	{
		Texture* texture = myAssetLoader->LoadTexture(texturePair.first);
		if (!texture)
		{
			Log::Logger::Print(Log::Severity::Error, Log::Category::World, "Error loading dummy data");
			return;
		}

		texture->myType = texturePair.second;
		myTextureLibrary->CompileTexture(*texture);
		myTextureLibrary->myTextures.push_back(*texture);
	}

	myModels.push_back(*model);

	Shader* vertexShader = myAssetLoader->LoadShader("../../../Data/Shaders/NormalVertexShader.glsl", ShaderType::Vertex);
	Shader* fragmentShader = myAssetLoader->LoadShader("../../../Data/Shaders/NormalFragmentShader.glsl", ShaderType::Fragment);

	if (!vertexShader || !fragmentShader)
	{
		Log::Logger::Print(Log::Severity::Error, Log::Category::World, "Error loading dummy data");
		return;
	}

	myShaderLibrary->AddShader(*vertexShader);
	myShaderLibrary->AddShader(*fragmentShader);
	myShaderLibrary->CompileCurrentShaders();
	myShaderLibrary->AttachCurrentShaders();
}

void World::Update()
{
}

void World::Destroy()
{
	delete myAssetLoader;
	delete myShaderLibrary;
	delete myTextureLibrary;
	delete myCamera;
	myModels.clear();
}
