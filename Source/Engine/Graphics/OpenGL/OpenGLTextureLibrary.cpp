#include "OpenGLTextureLibrary.h"

#include "OpenGLError.h"

OpenGLTextureLibrary::OpenGLTextureLibrary() : TextureLibrary()
{
}

OpenGLTextureLibrary::~OpenGLTextureLibrary()
{
}

void OpenGLTextureLibrary::CompileTexture(Texture& aTexture)
{
	for (const Texture& texture : myTextures)
	{
		if (texture.mySource == aTexture.mySource)
		{
			free(aTexture.mySource);
			Log::Logger::Print(Log::Severity::Message, Log::Category::Rendering, "Texture already exists: %s", aTexture.myName);
			return;
		}
	}

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
