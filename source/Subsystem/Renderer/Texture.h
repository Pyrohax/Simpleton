#pragma once

#include <string>

struct Texture
{
	std::string myName;
	unsigned char* mySource;
	unsigned int myID;
	int myWidth;
	int myHeight;
	int myComponents;
};
