#include "CameraWidget.h"

#include "../../Core/Engine.h"
#include "../../World/Entity.h"
#include "../../World/World.h"
#include "../../World/CameraComponent.h"

UI::CameraWidget::CameraWidget(ImguiWrapper* aWrapper, const std::string& aTitle)
	: Widget(aWrapper, aTitle)
	, myTitle(aTitle)
{
}

void UI::CameraWidget::Tick()
{
	Engine& engine = Engine::GetInstance();
	World& world = *engine.GetWorld();
	Entity& camera = world.GetCamera();
	CameraComponent& cameraComponent = camera.GetComponent<CameraComponent>();

	ImGui::Text("Front x:%0.f y:%0.f z:%0.f", cameraComponent.GetFront().x, cameraComponent.GetFront().y, cameraComponent.GetFront().z);
	ImGui::Text("Up x:%0.f y:%0.f z:%0.f", cameraComponent.GetUp().x, cameraComponent.GetUp().y, cameraComponent.GetUp().z);
	ImGui::Text("Right x:%0.f y:%0.f z:%0.f", cameraComponent.GetRight().x, cameraComponent.GetRight().y, cameraComponent.GetRight().z);
	ImGui::Text("FOV: %0.f", cameraComponent.GetFieldOfView());
	ImGui::Text("Position x:%f y:%f z:%f", cameraComponent.GetPosition().x, cameraComponent.GetPosition().y, cameraComponent.GetPosition().z);
	ImGui::Text("Direction x:%f y:%f z:%f", cameraComponent.GetDirection().x, cameraComponent.GetDirection().y, cameraComponent.GetDirection().z);
}
