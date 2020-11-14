#include "Editor.h"

#include "Core/Engine.h"

Editor::Editor()
{
}

Editor::~Editor()
{
}

void Editor::Initialize()
{
	Engine& engine = Engine::GetInstance();
	engine.Initialize();
}

void Editor::Tick()
{
	Engine& engine = Engine::GetInstance();
	engine.Update();
}
