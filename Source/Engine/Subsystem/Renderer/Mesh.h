#pragma once

#include "Vertex.h"

struct Mesh
{
	std::vector<Vertex> myVertices;
	std::vector<unsigned int> myIndices;
};
