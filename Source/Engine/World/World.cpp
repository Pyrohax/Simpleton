#include "World.h"

#include "AssetLoader.h"
#include "Camera.h"
#include "../Core/Logger.h"
#include "../Graphics/Texture.h"
#include "../Graphics/OpenGL/ShaderLibrary.h"
#include "../Graphics/OpenGL/TextureLibrary.h"

World::World()
	: myAssetLoader(nullptr)
	, myShaderLibrary(nullptr)
{
	myAssetLoader = new AssetLoader();
	myShaderLibrary = new ShaderLibrary();
	myTextureLibrary = new TextureLibrary();
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
		Log::Print(LogType::PROBLEM, "Error loading dummy data");
		return;
	}

	for (const std::pair<std::string, TextureType>& texturePair : model->myTextureMap)
	{
		Texture* texture = myAssetLoader->LoadTexture(texturePair.first);
		if (!texture)
		{
			Log::Print(LogType::PROBLEM, "Error loading dummy data");
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
		Log::Print(LogType::PROBLEM, "Error loading dummy data");
		return;
	}

	myShaderLibrary->myShaders.push_back(*vertexShader);
	myShaderLibrary->myShaders.push_back(*fragmentShader);

	myShaderLibrary->CompileShader(myShaderLibrary->myShaders[0]);
	myShaderLibrary->CompileShader(myShaderLibrary->myShaders[1]);

	myShaderLibrary->AttachShaders(myShaderLibrary->myShaders[0], myShaderLibrary->myShaders[1]);
}

void World::Update()
{
}

void World::Destroy()
{
	delete myAssetLoader;
	delete myShaderLibrary;
	delete myTextureLibrary;
	myModels.clear();
}
