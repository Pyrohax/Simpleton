#pragma once

#include "../TextureLibrary.h"

#include <vector>

class OpenGLTextureLibrary final : public TextureLibrary
{
public:
	OpenGLTextureLibrary();
	~OpenGLTextureLibrary();

	void CompileTexture(Texture& aTexture) override;

public:
	std::vector<Texture> myTextures;
};
