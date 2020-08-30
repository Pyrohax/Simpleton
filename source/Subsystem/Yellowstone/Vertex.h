#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <assimp/vector2.h>
#include <assimp/vector3.h>

struct Vertex
{
	glm::vec3 myPosition;
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
			size_t test = 0;
			CombineHash(test, aVertex.myPosition, aVertex.myTextureCoordinates);
			return test;
		}
	};
}

static inline const glm::vec3& CastToVec3(const aiVector3D& aVector3D) { return glm::vec3(aVector3D.x, aVector3D.y, aVector3D.z); }
static inline const glm::vec2& CastToVec2(const aiVector2D& aVector2D) { return glm::vec2(aVector2D.x, aVector2D.y); }
