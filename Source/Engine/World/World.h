#pragma once

#include "../Graphics/Model.h"

#include <vector>

class AssetLoader;
class Camera;
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
	TextureLibrary& GetTextureLibrary() { return *myTextureLibrary; }
	AssetLoader& GetAssetLoader() { return *myAssetLoader; }
	Camera& GetCamera() { return *myCamera; }

public:
	std::vector<Model> myModels;

private:
	AssetLoader* myAssetLoader;
	ShaderLibrary* myShaderLibrary;
	TextureLibrary* myTextureLibrary;
	Camera* myCamera;
};
