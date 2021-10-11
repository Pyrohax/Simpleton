#pragma once

#include "Graphics/UI/Overlay.h"

class EditorOverlay : public UI::Overlay
{
public:
	EditorOverlay();
	~EditorOverlay();

	void Tick() override;
};
