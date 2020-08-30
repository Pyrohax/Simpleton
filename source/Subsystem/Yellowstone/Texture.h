#pragma once

#include <string>

class Texture
{
public:
	Texture(const std::string& aPath);
	~Texture();

	const unsigned int GetID() const { return myID; }
	const int GetWidth() const { return myWidth; }
	const int GetHeight() const { return myHeight; }

private:
	unsigned int myID;
	int myWidth;
	int myHeight;
	int myComponents;
};
