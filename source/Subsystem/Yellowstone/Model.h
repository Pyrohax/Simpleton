#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include <vector>
#include <string>

struct Vertex;
class Texture;

struct Mesh
{
	std::vector<Vertex> myVertices;
	std::vector<unsigned int> myIndices;
};

class Model
{
public:
	Model(const std::string aPath);
	~Model();

	const std::vector<Mesh>& GetMeshes() const { return myMeshes; }
	const std::vector<Texture*>& GetTextures() const { return myTextures; }
	const glm::mat4 GetModelMatrix() const { return myModelMatrix; }
	const glm::vec3 GetPosition() const { return myPosition; }

private:
	bool DoesFileExist(const std::string& aPath);
	void LoadOBJ(const std::string aPath, const std::string aBaseDirectory);
	void LoadFBX(const std::string aPath);

public:
	unsigned int myVertexArrayObject;
	unsigned int myVertexBufferObject;
	unsigned int myElementBufferObject;
	unsigned int myColorBufferObject;
	unsigned int myTextureUnit;

private:
	std::vector<Mesh> myMeshes;
	std::vector<Texture*> myTextures;
	glm::mat4 myModelMatrix;
	glm::vec3 myPosition;
};
