#pragma once

#include "../ShaderLibrary.h"

class VulkanShaderLibrary final : public ShaderLibrary
{
public:
	VulkanShaderLibrary();
	~VulkanShaderLibrary();

	void CreateProgram() override {}
	void AddShader(Shader& aShader) override {}
	void CompileShader(Shader& aShader) override {}
	void CompileCurrentShaders() override {}
	void AttachShaders(const Shader& aVertexShader, const Shader& aFragmentShader) override {}
	void AttachCurrentShaders() override {}
	void BindShaders() override {}
	void UnbindShaders() override {}

	void SetInt(const std::string& aName, int aValue) override {}
	void SetFloat(const std::string& aName, float aValue) override {}
	void SetVector3Float(const std::string& aName, const glm::vec3& aValue) override {}
	void SetVector4Float(const std::string& aName, const glm::vec4& aValue) override {}
	void SetMatrix3Float(const std::string& aName, const glm::mat3& aValue) override {}
	void SetMatrix4Float(const std::string& aName, const glm::mat4& aValue) override {}

	const std::vector<Shader>& GetShaders() const override { return myShaders; }
	const unsigned int GetProgramID() const override { return 0; }

	unsigned int GetShaderType(ShaderType aType) override { return 0; }

private:
	std::vector<Shader> myShaders;
};
