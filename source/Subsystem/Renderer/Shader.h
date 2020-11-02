#pragma once

#include <string>
#include <glm/vec4.hpp>

enum class ShaderType
{
    None = 0,
    Vertex = 1,
    Fragment = 2
};

struct Shader
{
    std::string mySource;
    std::string myName;
    std::string myFileExtension;
    ShaderType myShaderType;
    unsigned int myID;
    unsigned int myType;
};
