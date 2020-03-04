#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "Engine.h"

int main(int argc, char** argv)
{
	Engine engine;
	engine.Init();
	engine.Update();
	engine.Terminate();
	return 0;
}