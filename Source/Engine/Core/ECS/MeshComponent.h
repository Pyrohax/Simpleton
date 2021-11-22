#pragma once

#include "../../Graphics/Vertex.h"

struct MeshComponent
{
public:
	std::vector<Vertex> myVertices;
	std::vector<unsigned int> myIndices;
};
