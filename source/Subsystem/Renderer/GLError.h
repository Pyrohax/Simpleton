#pragma once

#include "../../Utility/Logger.h"

#include <glad/glad.h>

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

        Log::Print(LogType::PROBLEM, "%s", errorString);
    }
}

static void GLAPIENTRY ErrorCallback(GLenum aSource, GLenum aType, GLuint anID, GLenum aSeverity, GLsizei /*aLength*/, const GLchar* aMessage, const void* /*aUserParam*/)
{
    Log::Print(LogType::PROBLEM, "Message from OpenGL: Source: 0x%x Type: 0x%x Id: 0x%x Severity: 0x%x", aSource, aType, anID, aSeverity);
    Log::Print(LogType::PROBLEM, "%s", aMessage);
}
