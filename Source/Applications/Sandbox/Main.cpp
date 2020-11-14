#include "Engine.h"

#include <stdio.h>
#include <stdlib.h>
#include <wtypes.h>

#if defined(_WIN32) || defined(_WIN64)
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow)
{
	Engine& engine = Engine::GetInstance();
	engine.Init();
	engine.Update();
	engine.Terminate();

	return 0;
}
#else
int main(int /*argc*/, char** /*argv*/)
{
	Engine& engine = Engine::GetInstance();
	engine.Init();
	engine.Update();
	engine.Terminate();

	return 0;
}
#endif