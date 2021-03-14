#include "Editor.h"

#include "Core/Engine.h"
#include "Core/EngineContext.h"
#include "Graphics/Yellowstone.h"
#include "Graphics/UI/ImguiWrapper.h"
#include "EditorOverlay.h"

Editor::Editor()
{
}

Editor::~Editor()
{
}

void Editor::Initialize()
{
	Engine& engine = Engine::GetInstance();
	engine.Initialize(BuildType::Editor);

	Yellowstone* yellowstone = engine.GetContext()->GetSubsystem<Yellowstone>();
	yellowstone->GetImguiWrapper()->AddOverlay(std::make_shared<EditorOverlay>());
}

void Editor::Tick()
{
	Engine& engine = Engine::GetInstance();
	engine.Update();
}
