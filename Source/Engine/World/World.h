#pragma once

#include "../Graphics/Model.h"

#include <vector>

class AssetLoader;
class Entity;
class EntityComponentSystem;

class World
{
public:
	World(EntityComponentSystem* aEntityComponentSystem);
	~World();

	void Initialize();

	void LoadDefaultData();
	void LoadAndAddModel(const std::string& aPath);
	void LoadAndAddShaders(const std::string& aVertexShaderPath, const std::string& aFragmentShaderPath);

	AssetLoader& GetAssetLoader() { return *myAssetLoader.get(); }
	Entity& GetCamera() { return *myCamera; }
	Entity& GetLighting() { return *myLighting; }

	const std::vector<Model>& GetModels() const { return myModels; }
	std::vector<Model>& GetModels() { return myModels; }

private:
	std::vector<Model> myModels;
	std::unique_ptr<AssetLoader> myAssetLoader;
	Entity* myLighting;
	Entity* myCamera;
};
