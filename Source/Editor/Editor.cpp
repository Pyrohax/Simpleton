#include "Editor.h"

#include "Core/Engine.h"
#include "Core/EngineContext.h"
#include "EditorOverlay.h"
#include "Graphics/UI/ImguiWrapper.h"
#include "Graphics/Yellowstone.h"

Editor::Editor()
{}

Editor::~Editor()
{}

void Editor::Initialize()
{
	Engine& engine = Engine::GetInstance();
	engine.Initialize(BuildType::Editor);
	Yellowstone* yellowstone = engine.GetContext().GetSubsystem<Yellowstone>();
	if (!yellowstone)
		return;

	UI::ImguiWrapper* imguiWrapper = yellowstone->GetImguiWrapper();
	if (!imguiWrapper)
		return;

	yellowstone->GetImguiWrapper()->AddOverlay(std::make_shared<EditorOverlay>());
}

void Editor::Update()
{
	Engine& engine = Engine::GetInstance();
	engine.Update();
}

void Editor::Terminate()
{
	Engine& engine = Engine::GetInstance();
	engine.Shutdown();
}
