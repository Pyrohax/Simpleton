#pragma once

#include "Graphics/UI/Overlay.h"

class EditorOverlay : public UI::Overlay
{
public:
	EditorOverlay();
	~EditorOverlay();

	void Tick() override;

private:

};

EditorOverlay::EditorOverlay()
	: Overlay(true)
{
}

EditorOverlay::~EditorOverlay()
{
}

inline void EditorOverlay::Tick()
{
	ImGui::Text("Test");
}
