#pragma once

#include <string>

enum class TextureType
{
	Alpha,
	Ambient,
	Bump,
	Diffuse,
	Displacement,
	Reflection,
	Specular,
	SpecularHighlight
};

struct Texture
{
	std::string myName;
	unsigned char* mySource;
	unsigned int myID;
	TextureType myType;
	int myWidth;
	int myHeight;
	int myComponents;
};
