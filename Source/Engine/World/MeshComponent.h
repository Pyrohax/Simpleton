#pragma once

#include "../Graphics/Vertex.h"

struct MeshComponent
{
public:
	MeshComponent() {}

	std::vector<Vertex> myVertices;
	std::vector<unsigned int> myIndices;
};
