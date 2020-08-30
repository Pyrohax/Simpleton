#pragma once

class Shader;

class ShaderLibrary
{
public:
	ShaderLibrary();
	~ShaderLibrary();

	void BindShaders();

	const unsigned int GetProgramID() const { return myProgramID; }

private:
	void AttachShaders(const Shader& aVertexShader, const Shader& aFragmentShader);

private:
	Shader* myVertexShader;
	Shader* myFragmentShader;
	unsigned int myProgramID;
};
