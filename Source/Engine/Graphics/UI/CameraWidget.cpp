#include "CameraWidget.h"

#include "../../Core/Engine.h"
#include "../../World/Camera.h"
#include "../../World/World.h"

UI::CameraWidget::CameraWidget(ImguiWrapper* aWrapper, const std::string& aTitle)
	: Widget(aWrapper, aTitle)
	, myTitle(aTitle)
{
}

void UI::CameraWidget::Tick()
{
    Engine& engine = Engine::GetInstance();
    World& world = *engine.GetWorld();
	Camera& camera = world.GetCamera();

	ImGui::Text("Front x:%0.f y:%0.f z:%0.f", camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
	ImGui::Text("Up x:%0.f y:%0.f z:%0.f", camera.GetUp().x, camera.GetUp().y, camera.GetUp().z);
	ImGui::Text("Right x:%0.f y:%0.f z:%0.f", camera.GetRight().x, camera.GetRight().y, camera.GetRight().z);
	ImGui::Text("FOV: %0.f", camera.GetFieldOfView());
	ImGui::Text("Position x:%f y:%f z:%f", camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
	ImGui::Text("Direction x:%f y:%f z:%f", camera.GetDirection().x, camera.GetDirection().y, camera.GetDirection().z);
}
