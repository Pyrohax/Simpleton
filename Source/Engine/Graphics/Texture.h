#pragma once

#include <string>

enum class TextureType
{
	None,
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
	Texture()
		: myName("")
		, myFileExtension("")
		, mySource(0)
		, myID(0)
		, myType(TextureType::None)
		, myWidth(0)
		, myHeight(0)
		, myComponents(0)
	{
	}

	std::string myName;
	std::string myFileExtension;
	unsigned char* mySource;
	unsigned int myID;
	TextureType myType;
	int myWidth;
	int myHeight;
	int myComponents;
};
