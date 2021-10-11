#pragma once

#include "Texture.h"

#include <vector>

class TextureLibrary
{
public:
	TextureLibrary() {}

	virtual void CompileTexture(Texture& aTexture) = 0;

public:
	std::vector<Texture> myTextures;
};
