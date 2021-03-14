#include "EditorOverlay.h"

#include "Core/Engine.h"
#include "World/EntityFactory.h"
#include "World/World.h"

EditorOverlay::EditorOverlay()
	: Overlay(true)
{
}

EditorOverlay::~EditorOverlay()
{
}

inline void EditorOverlay::Tick()
{
	EntityFactory& entityFactory = Engine::GetInstance().GetWorld()->GetEntityFactory();
	if (ImGui::Button("Add Entity"))
	{
		entityFactory.CreateEntity();
	}

	for (int index = 0; index < entityFactory.GetEntityCount(); index++)
	{
		ImGui::Text(entityFactory.GetEntityByIndex(index)->myName.c_str());
	}
}
