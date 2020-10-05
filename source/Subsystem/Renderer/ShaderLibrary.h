#pragma once

#include "Shader.h"

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

	unsigned int GetShaderType(ShaderType aType);
	const unsigned int GetProgramID() const { return myProgramID; }

public:
	std::vector<Shader> myShaders;

private:
	unsigned int myProgramID;
};
