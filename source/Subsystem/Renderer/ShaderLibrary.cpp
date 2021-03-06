#include "ShaderLibrary.h"

#include "GLError.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <string>

#include <filesystem>

ShaderLibrary::ShaderLibrary()
    : myProgramID(0)
{
}

ShaderLibrary::~ShaderLibrary()
{
    if (myProgramID)
        glDeleteProgram(myProgramID);

    myShaders.clear();
}

void ShaderLibrary::CreateProgram()
{
    myProgramID = glCreateProgram();
}

void ShaderLibrary::CompileShader(Shader& aShader)
{
    Log::Print(LogType::MESSAGE, "Compiling %s", aShader.myName.c_str());

    aShader.myType = GetShaderType(aShader.myShaderType);
    aShader.myID = glCreateShader(aShader.myType);
    
    const GLchar* sourceCStr = aShader.mySource.c_str();
    glShaderSource(aShader.myID, 1, &sourceCStr, nullptr);
    glCompileShader(aShader.myID);
    
    GLint isCompiled = GL_FALSE;
    glGetShaderiv(aShader.myID, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxInfoLength = 0;
        glGetShaderiv(aShader.myID, GL_INFO_LOG_LENGTH, &maxInfoLength);
    
        if (maxInfoLength > 0)
        {
            std::vector<GLchar> infoLog(maxInfoLength);
            glGetShaderInfoLog(aShader.myID, maxInfoLength, &maxInfoLength, &infoLog[0]);
            Log::Print(LogType::PROBLEM, "%s", &infoLog[0]);
        }
    }
    
    Log::Print(LogType::SUCCESS, "Compiled %s", aShader.myName.c_str());
}

void ShaderLibrary::AttachShaders(const Shader& aVertexShader, const Shader& aFragmentShader)
{
    Log::Print(LogType::MESSAGE, "Linking program [%i] to %s", myProgramID, aVertexShader.myName.c_str());
    Log::Print(LogType::MESSAGE, "Linking program [%i] to %s", myProgramID, aFragmentShader.myName.c_str());

    const unsigned int vertexShaderID = aVertexShader.myID;
    const unsigned int fragmentShaderID = aFragmentShader.myID;
    glAttachShader(myProgramID, vertexShaderID);
    glAttachShader(myProgramID, fragmentShaderID);
    glLinkProgram(myProgramID);

    GLint isLinked = GL_FALSE;
    glGetProgramiv(myProgramID, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE)
    {
        GLchar infoLog[512];
        glGetProgramInfoLog(myProgramID, 512, nullptr, infoLog);
        Log::Print(LogType::PROBLEM, "%s", infoLog);
    }

    glDetachShader(myProgramID, vertexShaderID);
    glDetachShader(myProgramID, fragmentShaderID);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    CheckGLError();
}

void ShaderLibrary::BindShaders()
{
    glUseProgram(myProgramID);
}

void ShaderLibrary::SetInt(const std::string& aName, int aValue)
{
    GLint location = glGetUniformLocation(myProgramID, aName.c_str());
    glUniform1i(location, aValue);
}

void ShaderLibrary::SetFloat(const std::string& aName, float aValue)
{
    GLint location = glGetUniformLocation(myProgramID, aName.c_str());
    glUniform1f(location, aValue);
}

void ShaderLibrary::SetVector3Float(const std::string& aName, const glm::vec3& aValue)
{
    GLint location = glGetUniformLocation(myProgramID, aName.c_str());
    glUniform3f(location, aValue.x, aValue.y, aValue.z);
}

void ShaderLibrary::SetVector4Float(const std::string& aName, const glm::vec4& aValue)
{
    GLint location = glGetUniformLocation(myProgramID, aName.c_str());
    glUniform4f(location, aValue.x, aValue.y, aValue.z, aValue.w);
}

void ShaderLibrary::SetMatrix3Float(const std::string& aName, const glm::mat3& aValue)
{
    GLint location = glGetUniformLocation(myProgramID, aName.c_str());
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(aValue));
}

void ShaderLibrary::SetMatrix4Float(const std::string& aName, const glm::mat4& aValue)
{
    GLint location = glGetUniformLocation(myProgramID, aName.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(aValue));
}

unsigned int ShaderLibrary::GetShaderType(ShaderType aType)
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
