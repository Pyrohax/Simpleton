#pragma once

#include "../Graphics/Model.h"

#include <vector>

class AssetLoader;
class Camera;

class World
{
public:
	World();
	~World();

	void LoadDummyData();
	void Update();
	void Destroy();

	AssetLoader& GetAssetLoader() { return *myAssetLoader; }
	Camera& GetCamera() { return *myCamera; }

public:
	std::vector<Model> myModels;

private:
	AssetLoader* myAssetLoader;
	Camera* myCamera;
};
