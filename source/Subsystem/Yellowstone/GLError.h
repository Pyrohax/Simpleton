#pragma once

#include <glad/glad.h>

#include <cstdio>

#define ASSERT(x) if (!(x)) __debugbreak();

static inline void CheckGLError()
{
    while (true)
    {
        const GLenum error = glGetError();
        if (error == GL_NO_ERROR)
            return;

        const char* errorString;
        switch (error)
        {
            case GL_NO_ERROR:
                errorString = "No error";
                break;
            case GL_INVALID_ENUM:
                errorString = "Invalid enum";
                break;
            case GL_INVALID_VALUE:
                errorString = "Invalid value";
                break;
            case GL_INVALID_OPERATION:
                errorString = "Invalid operation";
                break;
            case GL_STACK_OVERFLOW:
                errorString = "Stack overflow";
                break;
            case GL_STACK_UNDERFLOW:
                errorString = "Stack underflow";
                break;
            case GL_OUT_OF_MEMORY:
                errorString = "Out of memory";
                break;
            default:
                errorString = "Unknown error";
                break;
        }

        printf("%s\n", errorString);
    }
}

static void GLAPIENTRY ErrorCallback(GLenum aSource, GLenum aType, GLuint anID, GLenum aSeverity, GLsizei /*aLength*/, const GLchar* aMessage, const void* /*aUserParam*/)
{
    printf("Message from OpenGL:\nSource: 0x%x\nType: 0x%x\n Id: 0x%x\nSeverity: 0x%x\n", aSource, aType, anID, aSeverity);
    printf("%s\n", aMessage);
}
