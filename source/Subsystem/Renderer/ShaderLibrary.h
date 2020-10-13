#pragma once

#include "Shader.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <vector>

class ShaderLibrary
{
public:
	ShaderLibrary();
	~ShaderLibrary();

	void CreateProgram();
	void CompileShader(Shader& aShader);
	void AttachShaders(const Shader& aVertexShader, const Shader& aFragmentShader);
	void BindShaders();

	void SetInt(const std::string& aName, int aValue);
	void SetFloat(const std::string& aName, float aValue);
	void SetVector3Float(const std::string& aName, const glm::vec3& aValue);
	void SetVector4Float(const std::string& aName, const glm::vec4& aValue);
	void SetMatrix3Float(const std::string& aName, const glm::mat3& aValue);
	void SetMatrix4Float(const std::string& aName, const glm::mat4& aValue);

	unsigned int GetShaderType(ShaderType aType);
	const unsigned int GetProgramID() const { return myProgramID; }

public:
	std::vector<Shader> myShaders;

private:
	unsigned int myProgramID;
};
