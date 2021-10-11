#pragma once

#include "../TextureLibrary.h"

#include <vector>

class OpenGLTextureLibrary : public TextureLibrary
{
public:
	OpenGLTextureLibrary();
	~OpenGLTextureLibrary();

	void CompileTexture(Texture& aTexture) override;

public:
	std::vector<Texture> myTextures;
};
