#pragma once

#include "../ECS/Core/Entity.h"
#include "../Graphics/Model.h"

#include <vector>

class AssetLoader;
class Coordinator;

class World
{
public:
	World(Coordinator* aCoordinator);
	~World();

	void Initialize();

	void LoadDefaultData();
	void LoadAndAddModel(const std::string& aPath);
	void LoadAndAddShaders(const std::string& aVertexShaderPath, const std::string& aFragmentShaderPath);

	AssetLoader& GetAssetLoader() { return *myAssetLoader.get(); }
	Entity& GetCamera() { return *myCamera.get(); }
	Entity& GetLighting() { return *myLighting.get(); }

	const std::vector<Model>& GetModels() const { return myModels; }
	std::vector<Model>& GetModels() { return myModels; }

private:
	std::vector<Model> myModels;
	std::unique_ptr<AssetLoader> myAssetLoader;
	std::unique_ptr<Entity> myLighting;
	std::unique_ptr<Entity> myCamera;
};
