#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

struct Vertex
{
	glm::vec3 myPosition;
	glm::vec3 myNormal;
	glm::vec3 myTangent;
	glm::vec2 myTextureCoordinates;

	bool operator==(const Vertex& aOther) const
	{
		return myPosition == aOther.myPosition &&myTextureCoordinates == aOther.myTextureCoordinates;
	}
};

inline void CombineHash(std::size_t& aSeed) {}

template <typename T, typename... Rest>
inline void CombineHash(std::size_t& aSeed, const T& aValue, Rest... aRest)
{
	std::hash<T> hasher;
	aSeed ^= hasher(aValue) + 0x9e3779b9 + (aSeed << 6) + (aSeed >> 2);
	CombineHash(aSeed, aRest...);
}

namespace std
{
	template<> struct hash<Vertex>
	{
		size_t operator()(Vertex const& aVertex) const
		{
			size_t seed = 0;
			CombineHash(seed, aVertex.myPosition, aVertex.myTextureCoordinates);
			return seed;
		}
	};
}
