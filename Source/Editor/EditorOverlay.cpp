#include "EditorOverlay.h"

#include "Core/Engine.h"
#include "Core/EngineContext.h"
#include "Graphics/Yellowstone.h"
#include "World/EntityFactory.h"
#include "World/MeshComponent.h"
#include "World/World.h"

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
}
