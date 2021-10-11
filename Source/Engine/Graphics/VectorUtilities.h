#pragma once

#ifdef USE_ASSIMP
#include <assimp/vector2.h>
#include <assimp/vector3.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

static inline glm::vec3 CastToVec3(const aiVector3D& aVector3D) { return glm::vec3(aVector3D.x, aVector3D.y, aVector3D.z); }
static inline glm::vec2 CastToVec2(const aiVector2D& aVector2D) { return glm::vec2(aVector2D.x, aVector2D.y); }
#endif // USE_ASSIMP
