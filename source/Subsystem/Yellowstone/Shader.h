#pragma once

#include <string>
#include <glm/vec4.hpp>

enum class ShaderType
{
    None = 0,
    Vertex = 1,
    Fragment = 2
};

class Shader
{
public:
    Shader(const std::string& aPath, ShaderType aType);
    ~Shader();

    void SetUniformLocation(unsigned int aProgramID, std::string& aName, glm::vec4 aLocation);
    int GetUniformLocation(unsigned int aProgramID, const std::string& aName);

    const std::string& GetPath() const { return myPath; }
    const std::string& GetName() const { return myName; }
    const ShaderType GetShaderType() const { return myShaderType; }
    const unsigned int GetID() const { return myID; }

private:
    void Compile(const std::string& aShaderSource);
    std::string ReadFile(const std::string& aPath);
    std::string GetNameFromPath(const std::string& aPath);
    unsigned int GetShaderType(ShaderType aType);

private:
    ShaderType myShaderType;
    unsigned int myID;
    unsigned int myType;
    std::string myPath;
    std::string myName;
};