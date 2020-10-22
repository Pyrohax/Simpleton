#pragma once

#include "Mesh.h"

#include <map>

enum class TextureType;

class Model
{
public:
	Model();
	~Model();

public:
	std::vector<Mesh> myMeshes;
	std::map<std::string, TextureType> myTextureMap;
	glm::mat4 myModelMatrix;
	glm::vec3 myPosition;
	std::string myName;
	std::string myFileExtension;
	unsigned int myVertexArrayObject;
	unsigned int myVertexBufferObject;
	unsigned int myElementBufferObject;
	unsigned int myColorBufferObject;
};
