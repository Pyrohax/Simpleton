#include "Engine.h"
#include "Utility/Timer.h"
#include "Utility/Assert.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

int main(int argc, char** argv)
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