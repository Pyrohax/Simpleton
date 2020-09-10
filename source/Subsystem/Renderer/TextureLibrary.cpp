#include "TextureLibrary.h"

#include "GLError.h"

TextureLibrary::TextureLibrary()
{
}

TextureLibrary::~TextureLibrary()
{
}

void TextureLibrary::CompileTexture(Texture& aTexture)
{
	glGenTextures(1, &aTexture.myID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glBindTexture(GL_TEXTURE_2D, aTexture.myID);

	GLenum format = aTexture.myComponents == 3 ? GL_RGB : GL_RGBA;
	glTexImage2D(GL_TEXTURE_2D, 0, format, aTexture.myWidth, aTexture.myHeight, 0, format, GL_UNSIGNED_BYTE, aTexture.mySource);

	free(aTexture.mySource);

	CheckGLError();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	CheckGLError();
}
