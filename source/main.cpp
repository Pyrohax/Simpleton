#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "Engine.h"
#include "Timer.h"

int main(int argc, char** argv)
{

	Timer t;
	t.Start();
	{
		Engine engine;
		engine.Init();
		engine.Update();
		engine.Terminate();
	}

	t.Stop();
	t.Print();

	return 0;
}