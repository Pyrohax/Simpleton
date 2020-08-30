#include "Shader.h"

#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <vector>

Shader::Shader(const std::string& aPath, ShaderType aType)
    : myShaderType(aType)
    , myID(0)
    , myType(0)
    , myPath(aPath)
    , myName("")
{
    myName = GetNameFromPath(aPath);
    myType = GetShaderType(aType);

    std::string shaderSource = ReadFile(aPath);
    Compile(shaderSource);
}

Shader::~Shader()
{
}

std::string Shader::ReadFile(const std::string& aPath)
{
    std::string sourceResult;
    std::ifstream sourceStream(aPath, std::ios::in);

    if (!sourceStream.is_open())
    {
        printf("Failed to read file %s\n", aPath.c_str());
        return "";
    }

    std::stringstream sourceStringStream;
    sourceStringStream << sourceStream.rdbuf();
    sourceResult = sourceStringStream.str();
    sourceStream.close();

    return sourceResult;
}

void Shader::Compile(const std::string& aShaderSource)
{
    myID = glCreateShader(myType);

    printf("Compiling %s\n", myName.c_str());

    const GLchar* sourceCStr = aShaderSource.c_str();
    glShaderSource(myID, 1, &sourceCStr, nullptr);
    glCompileShader(myID);

    GLint isCompiled = GL_FALSE;
    glGetShaderiv(myID, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxInfoLength = 0;
        glGetShaderiv(myID, GL_INFO_LOG_LENGTH, &maxInfoLength);

        if (maxInfoLength > 0)
        {
            std::vector<GLchar> infoLog(maxInfoLength);
            glGetShaderInfoLog(myID, maxInfoLength, &maxInfoLength, &infoLog[0]);
            printf("%s\n", &infoLog[0]);
        }
    }

    printf("Compiled %s\n", myName.c_str());
}

void Shader::SetUniformLocation(unsigned int aProgramID, std::string& aName, glm::vec4 aLocation)
{
    glUniform4f(GetUniformLocation(aProgramID, aName), aLocation.x, aLocation.y, aLocation.z, aLocation.w);
}

int Shader::GetUniformLocation(unsigned int aProgramID, const std::string& aName)
{
    return glGetUniformLocation(aProgramID, aName.c_str());
}

std::string Shader::GetNameFromPath(const std::string& aPath)
{
    size_t lastSlash = aPath.find_last_of("/\\");
    lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
    size_t lastDot = aPath.rfind('.');
    size_t count = lastDot == std::string::npos ? aPath.size() - lastSlash : lastDot - lastSlash;
    return aPath.substr(lastSlash, count);
}

unsigned int Shader::GetShaderType(ShaderType aType)
{
    switch (aType)
    {
        case ShaderType::None:
            return GL_NONE;
        case ShaderType::Vertex:
            return GL_VERTEX_SHADER;
        case ShaderType::Fragment:
            return GL_FRAGMENT_SHADER;
        default:
            return GL_NONE;
    }
}
