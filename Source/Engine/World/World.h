#pragma once

#include "../Graphics/Model.h"
#include "Entity.h"

#include <vector>
#include "../Graphics/UI/WidgetIconType.h"

class AssetLoader;
class EntityFactory;

class World
{
public:
	World();
	~World();

	void Update();
	void Destroy();

	void LoadDefaultData();
	void LoadAndAddModel(const std::string& aPath);
	void LoadAndAddShaders(const std::string& aVertexShaderPath, const std::string& aFragmentShaderPath);

	AssetLoader& GetAssetLoader() { return *myAssetLoader; }
	Entity& GetCamera() { return *myCamera; }
	EntityFactory& GetEntityFactory() { return *myEntityFactory; }
	const Entity& GetLighting() const { return *myLighting; }

	const std::vector<Entity>& GetEntities() const { return myEntities; }
	const std::vector<Model>& GetModels() const { return myModels; }
	std::vector<Model>& GetModels() { return myModels; }

private:
	std::vector<Entity> myEntities;
	std::vector<Model> myModels;
	AssetLoader* myAssetLoader;
	EntityFactory* myEntityFactory;
	Entity* myLighting;
	Entity* myCamera;
};
