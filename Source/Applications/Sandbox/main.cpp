#include "Engine.h"
#include "Utility/Timer.h"
#include "Utility/Assert.h"

#include <stdio.h>
#include <stdlib.h>
#include <wtypes.h>

#if defined(_WIN32) || defined(_WIN64)
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow)
{
	Timer t;
	t.Start();
	
	Engine engine;
	engine.Init();
	engine.Update();
	engine.Terminate();
	
	t.Stop();
	t.Print();

	return 0;
}
#else
int main(int /*argc*/, char** /*argv*/)
{
	Timer t;
	t.Start();

	Engine engine;
	engine.Init();
	engine.Update();
	engine.Terminate();

	t.Stop();
	t.Print();

	return 0;
}
#endif