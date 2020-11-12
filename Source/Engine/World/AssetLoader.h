#pragma once

#include <string>

class Model;
struct Shader;
struct Texture;
enum class ShaderType;

class AssetLoader
{
public:
	AssetLoader();
	~AssetLoader();

	Model* LoadModel(const std::string& aPath);
	Shader* LoadShader(const std::string& aPath, ShaderType aShaderType);
	Texture* LoadTexture(const std::string& aPath);

private:
	Model* LoadOBJ(const std::string& aPath);
	Model* LoadFBX(const std::string& aPath);
	std::string ReadFile(const std::string& aPath);
	std::string GetNameFromPath(const std::string& aPath);
	std::string GetExtensionFromPath(const std::string& aPath);
	std::string GetDirectoryFromPath(const std::string& aPath);
	bool DoesFileExist(const std::string& aPath) const;
	void PrintModelInfo(const Model& aModel);
};
