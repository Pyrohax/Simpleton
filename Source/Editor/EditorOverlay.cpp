#include "EditorOverlay.h"

#include "Core/Engine.h"
#include "Core/EngineContext.h"
#include "Graphics/Yellowstone.h"
#include "World/AssetLoader.h"
#include "World/EntityFactory.h"
#include "World/MeshComponent.h"
#include "World/World.h"

#include <filesystem>

EditorOverlay::EditorOverlay()
	: Overlay(true)
{
}

EditorOverlay::~EditorOverlay()
{
}

void EditorOverlay::Tick()
{
	Engine& engine = Engine::GetInstance();
	World* world = engine.GetWorld();

	if (ImGui::Button("Load Dummy Data"))
	{
		world->LoadDummyData();

		EngineContext* engineContext = engine.GetContext();
		if (Yellowstone* yellowstone = engineContext->GetSubsystem<Yellowstone>())
		{
			yellowstone->CreateAssetBuffers(world->GetModels());
		}
	}

	EntityFactory& entityFactory = world->GetEntityFactory();
	if (ImGui::Button("Add Entity"))
	{
		entityFactory.CreateEntity();
	}

	for (int index = 0; index < entityFactory.GetEntityCount(); index++)
	{
		Entity& entity = entityFactory.GetEntityByIndex(index);
		ImGui::Text(entity.GetName().c_str());
		ImGui::SameLine();
		ImGui::Text(uuids::to_string(entity.GetUID()).c_str());
		ImGui::SameLine();
		if (const MeshComponent* meshComponent = entity.GetMesComponent())
		{
			ImGui::Text(uuids::to_string(meshComponent->myUID).c_str());
		}
		else if (ImGui::Button("Add Mesh Component"))
		{
			MeshComponent* meshComponent = new MeshComponent();
			entityFactory.AddComponent(entity.GetUID(), meshComponent);
		}
	}

	std::string dataPath = std::filesystem::current_path().string() + "\\..\\..\\..\\Data\\";

	if (ImGui::CollapsingHeader("Models"))
	{
		static ImGuiTextFilter filter;
		ImGui::Text("Filter usage:\n"
					"  \"\"         display all lines\n"
					"  \"xxx\"      display lines containing \"xxx\"\n"
					"  \"xxx,yyy\"  display lines containing \"xxx\" or \"yyy\"\n"
					"  \"-xxx\"     hide lines containing \"xxx\"");
		filter.Draw();

		std::string modelsPath = dataPath + "Models\\";
		for (const auto& entry : std::filesystem::recursive_directory_iterator(modelsPath))
		{
			if (!entry.path().has_extension())
				continue;

			auto findCharactersInString = [](const std::string& aString, const char* aCharacters)
			{
				return (aString.find(aCharacters) != std::string::npos);
			};

			const bool isTexture = findCharactersInString(entry.path().extension().string(), ".png") || findCharactersInString(entry.path().extension().string(), ".jpg");
			const bool isModel = findCharactersInString(entry.path().extension().string(), ".obj") || findCharactersInString(entry.path().extension().string(), ".fbx") || findCharactersInString(entry.path().extension().string(), ".gltf");

			if (!isTexture && !isModel)
				continue;

			const std::string& fullEntryPath = entry.path().string();
			const std::string file = entry.path().filename().string();

			if (filter.PassFilter(fullEntryPath.c_str()))
			{
				if (ImGui::Button(file.c_str()))
				{
					if (isTexture)
					{
						world->GetAssetLoader().LoadTexture(fullEntryPath);
					}
					else if (isModel)
					{
						world->LoadAndAddModel(fullEntryPath);

						EngineContext* engineContext = engine.GetContext();
						if (Yellowstone* yellowstone = engineContext->GetSubsystem<Yellowstone>())
						{
							yellowstone->CreateAssetBuffers(world->GetModels());
						}
					}
				}
			}
		}
	}

	if (ImGui::CollapsingHeader("Shaders"))
	{
		static ImGuiTextFilter filter;
		ImGui::Text("Filter usage:\n"
					"  \"\"         display all lines\n"
					"  \"xxx\"      display lines containing \"xxx\"\n"
					"  \"xxx,yyy\"  display lines containing \"xxx\" or \"yyy\"\n"
					"  \"-xxx\"     hide lines containing \"xxx\"");
		filter.Draw();

		std::vector<std::pair<std::string, std::string>> foundShaderPair;
		std::string shadersPath = dataPath + "Shaders\\";
		for (const auto& entry : std::filesystem::recursive_directory_iterator(shadersPath))
		{
			if (!entry.path().has_extension())
				continue;

			auto findCharactersInString = [](const std::string& aString, const char* aCharacters)
			{
				return (aString.find(aCharacters) != std::string::npos);
			};

			const bool isShader = findCharactersInString(entry.path().extension().string(), ".glsl");

			if (!isShader)
				continue;

			const std::string& fullEntryPath = entry.path().string();
			const std::string file = entry.path().filename().string();

			if (filter.PassFilter(fullEntryPath.c_str()))
			{
				foundShaderPair.push_back(std::make_pair(fullEntryPath, file));
			}
		}

		if (!foundShaderPair.empty())
		{
			for (int index = 0; index < foundShaderPair.size() - 1; index++)
			{
				if (ImGui::Button(foundShaderPair[index].second.c_str()))
				{
					world->LoadAndAddShaders(foundShaderPair[index + 1].first, foundShaderPair[index].first);
				}
			}
		}
	}
}
