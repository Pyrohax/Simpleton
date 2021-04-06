#pragma once

#include "Component.h"

#include "../Graphics/Vertex.h"

struct MeshComponent : public Component
{
public:
	MeshComponent() : Component() {}

	std::vector<Vertex> myVertices;
	std::vector<unsigned int> myIndices;
};
