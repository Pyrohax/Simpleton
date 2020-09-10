#include "World.h"

#include "AssetLoader.h"
#include "ShaderLibrary.h"
#include "TextureLibrary.h"

World::World()
	: myAssetLoader(nullptr)
	, myShaderLibrary(nullptr)
{
	myAssetLoader = new AssetLoader();
	myShaderLibrary = new ShaderLibrary();
	myTextureLibrary = new TextureLibrary();
}

World::~World()
{
}

void World::LoadDummyData()
{
	myShaderLibrary->CreateProgram();

	Model* model = myAssetLoader->LoadModel("../Data/Models/Planet/Planet.obj");
	if (!model)
	{
		printf("Error loading dummy data");
		return;
	}

	model->myTextureUnit = 0;
	myTextureLibrary->CompileTexture(model->myTextures[0]);

	myModels.push_back(*model);

	Shader* vertexShader = myAssetLoader->LoadShader("../Data/Shaders/ModelVertexShader.glsl", ShaderType::Vertex);
	Shader* fragmentShader = myAssetLoader->LoadShader("../Data/Shaders/ModelFragmentShader.glsl", ShaderType::Fragment);

	if (!vertexShader || !fragmentShader)
	{
		printf("Error loading dummy data");
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
