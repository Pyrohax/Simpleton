#include "ImguiDebugWidget.h"

#include "imgui.h"

ImguiDebugWidget::ImguiDebugWidget()
{
}

ImguiDebugWidget::~ImguiDebugWidget()
{
}

void ImguiDebugWidget::Draw(double aDeltaTime)
{
	ImGui::Text("Delta Time: %f", aDeltaTime);
	ImGui::Text("Press W/A/S/D to move the Camera, Left Shift and Spacebar to move up or down.", aDeltaTime);
	ImGui::Text("Press Left Control and move your mouse cursor to look around.", aDeltaTime);
}
