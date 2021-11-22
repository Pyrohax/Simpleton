#include "EditorOverlay.h"

#include "Core/Engine.h"
#include "Core/EngineContext.h"
#include "Graphics/Yellowstone.h"
#include "World/AssetLoader.h"
#include "World/LightingComponent.h"
#include "World/TransformComponent.h"
#include "World/World.h"
#include "ECS/Core/Coordinator.h"
#include "ECS/Core/Entity.h"

#include <filesystem>
#include <vector>

EditorOverlay::EditorOverlay()
	: Overlay(true)
{}

EditorOverlay::~EditorOverlay()
{}

void EditorOverlay::Tick()
{
	Engine& engine = Engine::GetInstance();
	World& world = engine.GetWorld();
	Entity& lighting = world.GetLighting();
	TransformComponent& lightingTransformComponent = lighting.GetComponent<TransformComponent>();
	ImGui::InputFloat3("Lighting Transform", lightingTransformComponent.GetRawPosition());
	LightingComponent& lightingComponent = lighting.GetComponent<LightingComponent>();
	ImGui::InputFloat3("Lighting Color", lightingComponent.GetRawColor());

	if (ImGui::Button("Add Entity"))
		engine.GetCoordinator().CreateEntity();

	const std::string dataPath = std::filesystem::current_path().string().substr(0, std::filesystem::current_path().string().length() - 23) + "Data\\";

	auto findCharactersInString = [](const std::string& aString, const char* aCharacters)
	{
		return (aString.find(aCharacters) != std::string::npos);
	};

	if (ImGui::CollapsingHeader("Models"))
	{
		static ImGuiTextFilter filter;
		ImGui::Text("Filter usage:\n"
					"  \"\"         display all lines\n"
					"  \"xxx\"      display lines containing \"xxx\"\n"
					"  \"xxx,yyy\"  display lines containing \"xxx\" or \"yyy\"\n"
					"  \"-xxx\"     hide lines containing \"xxx\"");
		filter.Draw();

		const std::string modelsPath = dataPath + "Models\\";

		for (const auto& entry : std::filesystem::recursive_directory_iterator(modelsPath))
		{
			if (!entry.path().has_extension())
				continue;

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
						world.GetAssetLoader().LoadTexture(fullEntryPath);
					}
					else if (isModel)
					{
						world.LoadAndAddModel(fullEntryPath);

						EngineContext& engineContext = engine.GetContext();
						if (Yellowstone* yellowstone = engineContext.GetSubsystem<Yellowstone>())
						{
							yellowstone->CreateAssetBuffers(world.GetModels());
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
		const std::string shadersPath = dataPath + "Shaders\\";
		for (const auto& entry : std::filesystem::recursive_directory_iterator(shadersPath))
		{
			if (!entry.path().has_extension())
				continue;

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
					world.LoadAndAddShaders(foundShaderPair[index + 1].first, foundShaderPair[index].first);
				}
			}
		}
	}
}
