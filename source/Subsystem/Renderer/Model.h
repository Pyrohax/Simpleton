#pragma once

#include "Mesh.h"
#include "Texture.h"

class Model
{
public:
	Model();
	~Model();

public:
	std::vector<Mesh> myMeshes;
	std::vector<Texture> myTextures;
	//std::vector<Material*> myMaterials;
	glm::mat4 myModelMatrix;
	glm::vec3 myPosition;
	std::string myName;
	unsigned int myVertexArrayObject;
	unsigned int myVertexBufferObject;
	unsigned int myElementBufferObject;
	unsigned int myColorBufferObject;
	unsigned int myTextureUnit;
};
