#include "Editor.h"

#include <stdio.h>
#include <stdlib.h>
#include <wtypes.h>

#if defined(_WIN32) || defined(_WIN64)
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow)
{
	Editor editor;
	editor.Initialize();
	editor.Tick();

	return 0;
}
#else
int main(int /*argc*/, char** /*argv*/)
{
	Editor editor;
	editor.Initialize();

	return 0;
}
#endif
