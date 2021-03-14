#pragma once

#include "../Graphics/Model.h"
#include "../ECS/Entity.h"

#include <vector>

class AssetLoader;
class Camera;
class EntityFactory;

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
	EntityFactory& GetEntityFactory() { return *myEntityFactory; }

	const std::vector<Entity>& GetEntities() const { return myEntities; }
	const std::vector<Model>& GetModels() const { return myModels; }
	std::vector<Model>& GetModels() { return myModels; }

private:
	AssetLoader* myAssetLoader;
	Camera* myCamera;
	EntityFactory* myEntityFactory;
	std::vector<Entity> myEntities;
	std::vector<Model> myModels;
};
