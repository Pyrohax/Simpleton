#include "EditorOverlay.h"

#include "Core/Engine.h"
#include "World/EntityFactory.h"
#include "World/World.h"

#include <uuid.h>

EditorOverlay::EditorOverlay()
	: Overlay(true)
{
}

EditorOverlay::~EditorOverlay()
{
}

void EditorOverlay::Tick()
{
	EntityFactory& entityFactory = Engine::GetInstance().GetWorld()->GetEntityFactory();
	if (ImGui::Button("Add Entity"))
	{
		entityFactory.CreateEntity();
	}

	for (int index = 0; index < entityFactory.GetEntityCount(); index++)
	{
		Entity* entity = entityFactory.GetEntityByIndex(index);
		ImGui::Text(entity->GetName().c_str());
		ImGui::SameLine();
		ImGui::Text(uuids::to_string(entity->GetUID()).c_str());
	}
}
