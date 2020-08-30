#include "ShaderLibrary.h"
#include "Shader.h"
#include "GLError.h"

#include <glad/glad.h>

#include <vector>
#include <string>

#include <filesystem>

ShaderLibrary::ShaderLibrary()
	: myVertexShader(nullptr)
    , myFragmentShader(nullptr)
    , myProgramID(0)
{
	myProgramID = glCreateProgram();

    myVertexShader = new Shader("../Data/Shaders/ModelVertexShader.glsl", ShaderType::Vertex);
    myFragmentShader = new Shader("../Data/Shaders/ModelFragmentShader.glsl", ShaderType::Fragment);

    AttachShaders(*myVertexShader, *myFragmentShader);
}

ShaderLibrary::~ShaderLibrary()
{
	glDeleteProgram(myProgramID);
}

void ShaderLibrary::AttachShaders(const Shader& aVertexShader, const Shader& aFragmentShader)
{
    printf("Linking program [%i] to %s\n", myProgramID, aVertexShader.GetName().c_str());
    printf("Linking program [%i] to %s\n", myProgramID, aFragmentShader.GetName().c_str());

    const unsigned int vertexShaderID = aVertexShader.GetID();
    const unsigned int fragmentShaderID = aFragmentShader.GetID();
    glAttachShader(myProgramID, vertexShaderID);
    glAttachShader(myProgramID, fragmentShaderID);
    glLinkProgram(myProgramID);

    GLint isLinked = GL_FALSE;
    glGetProgramiv(myProgramID, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE)
    {
        GLchar infoLog[512];
        glGetProgramInfoLog(myProgramID, 512, nullptr, infoLog);
        printf("%s\n", infoLog);
    }

    glDetachShader(myProgramID, vertexShaderID);
    glDetachShader(myProgramID, fragmentShaderID);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    CheckGLError();
}

void ShaderLibrary::BindShaders()
{
    if (!myVertexShader || !myFragmentShader)
        return;

    glUseProgram(myProgramID);
}
