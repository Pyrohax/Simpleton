#pragma once

#include "Texture.h"

class TextureLibrary
{
public:
	TextureLibrary();
	~TextureLibrary();

	void CompileTexture(Texture& aTexture);

public:
	//std::vector<Texture> myTextures;
};
