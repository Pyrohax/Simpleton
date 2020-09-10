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

public:
	std::vector<Model> myModels;

private:
	AssetLoader* myAssetLoader;
	ShaderLibrary* myShaderLibrary;
	TextureLibrary* myTextureLibrary;
};
