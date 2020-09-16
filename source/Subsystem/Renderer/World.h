#pragma once

#include "Model.h"

#include <vector>

class AssetLoader;
class ShaderLibrary;
class TextureLibrary;

class World
{
public:
	World();
	~World();

	void LoadDummyData();
	void Update();
	void Destroy();

	ShaderLibrary& GetShaderLibrary() { return *myShaderLibrary; }
	AssetLoader& GetAssetLoader() { return *myAssetLoader; }

public:
	std::vector<Model> myModels;

private:
	AssetLoader* myAssetLoader;
	ShaderLibrary* myShaderLibrary;
	TextureLibrary* myTextureLibrary;
};
