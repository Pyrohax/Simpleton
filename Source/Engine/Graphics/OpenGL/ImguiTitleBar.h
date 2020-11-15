#pragma once

class ImguiTitleBar
{
public:
	ImguiTitleBar();
	~ImguiTitleBar();

	void Draw(bool* aShowConsole, bool* aShowDemo, bool* aShowDebugWidget, bool* aShowCameraWidget);
};
