#pragma once

#include "Shader.h"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <vector>

class ShaderLibrary
{
public:
	ShaderLibrary() {}

	virtual void CreateProgram() = 0;
	virtual void AddShader(Shader& aShader) = 0;
	virtual void CompileShader(Shader& aShader) = 0;
	virtual void CompileCurrentShaders() = 0;
	virtual void AttachShaders(const Shader& aVertexShader, const Shader& aFragmentShader) = 0;
	virtual void AttachCurrentShaders() = 0;
	virtual void BindShaders() = 0;
	virtual void UnbindShaders() = 0;

	virtual void SetInt(const std::string& aName, int aValue) = 0;
	virtual void SetFloat(const std::string& aName, float aValue) = 0;
	virtual void SetVector3Float(const std::string& aName, const glm::vec3& aValue) = 0;
	virtual void SetVector4Float(const std::string& aName, const glm::vec4& aValue) = 0;
	virtual void SetMatrix3Float(const std::string& aName, const glm::mat3& aValue) = 0;
	virtual void SetMatrix4Float(const std::string& aName, const glm::mat4& aValue) = 0;

	virtual const std::vector<Shader>& GetShaders() const = 0;
	virtual const unsigned int GetProgramID() const = 0;

	virtual unsigned int GetShaderType(ShaderType aType) = 0;
};
