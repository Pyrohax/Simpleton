#pragma once

#include "../../Core/Logger.h"

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

        Log::Logger::Print(Log::Severity::Error, Log::Category::Rendering, "%s", errorString);
    }
}

static void GLAPIENTRY ErrorCallback(GLenum aSource, GLenum aType, GLuint anID, GLenum aSeverity, GLsizei /*aLength*/, const GLchar* aMessage, const void* /*aUserParam*/)
{
    char* source;
    char* type;
    char* severity;

    switch (aSource)
    {
        case GL_DEBUG_SOURCE_API:
            source = "API";
            break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            source = "WINDOW SYSTEM";
            break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            source = "SHADER COMPILER";
            break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            source = "THIRD PARTY";
            break;
        case GL_DEBUG_SOURCE_APPLICATION:
            source = "APPLICATION";
            break;
        case GL_DEBUG_SOURCE_OTHER:
            source = "OTHER";
            break;
        default:
            source = "UNKNOWN";
            break;
    }

    switch (aType)
    {
        case GL_DEBUG_TYPE_ERROR:
            type = "ERROR";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            type = "DEPRECATED BEHAVIOR";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            type = "UDEFINED BEHAVIOR";
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            type = "PORTABILITY";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            type = "PERFORMANCE";
            break;
        case GL_DEBUG_TYPE_OTHER:
            type = "OTHER";
            break;
        case GL_DEBUG_TYPE_MARKER:
            type = "MARKER";
            break;
        default:
            type = "UNKNOWN";
            break;
    }

    switch (aSeverity)
    {
        case GL_DEBUG_SEVERITY_HIGH:
            severity = "HIGH";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            severity = "MEDIUM";
            break;
        case GL_DEBUG_SEVERITY_LOW:
            severity = "LOW";
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            severity = "NOTIFICATION";
            break;
        default:
            severity = "UNKNOWN";
            break;
    }

    Log::Logger::Print(Log::Severity::Error, Log::Category::Rendering, "Message from OpenGL: Severity: %s Type: %s Source: %s Id: 0x%x", severity, type, source, anID);
    Log::Logger::Print(Log::Severity::Error, Log::Category::Rendering, "%s", aMessage);
}
