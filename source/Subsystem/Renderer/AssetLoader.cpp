#include "AssetLoader.h"

#include "Vertex.h"
#include "GLError.h"
#include "Texture.h"
#include "Model.h"
#include "Mesh.h"
#include "Shader.h"
#include "VectorUtilities.h"
#include "../../Utility/Logger.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <fstream>
#include <sstream>

#include <glm/vec3.hpp>
#include <glm/gtx/functions.hpp>

#include <algorithm>
#include <unordered_map>

AssetLoader::AssetLoader()
{
}

AssetLoader::~AssetLoader()
{
}

Model* AssetLoader::LoadModel(const std::string& aPath)
{
    if (!DoesFileExist(aPath))
    {
        Log::Print(LogType::PROBLEM, "File does not exist: %s", aPath.c_str());
        return nullptr;
    }

    std::size_t lastSlashIndex = aPath.find_last_of("/\\");
    std::size_t lastDotIndex = aPath.find_last_of(".");
    std::string baseDirectory = aPath.substr(0, lastSlashIndex + 1);
    std::string file = aPath.substr(lastSlashIndex + 1, aPath.length() - lastDotIndex);
    std::string extension = aPath.substr(lastDotIndex + 1, aPath.length());

    if (extension == "obj")
    {
       return LoadOBJ(aPath, file, baseDirectory);
    }
    else if (extension == "fbx")
    {
        return LoadFBX(aPath, file);
    }

    return nullptr;
}

Shader* AssetLoader::LoadShader(const std::string& aPath, ShaderType aShaderType)
{
    if (!DoesFileExist(aPath))
    {
        Log::Print(LogType::PROBLEM, "File does not exist: %s", aPath.c_str());
        return nullptr;
    }

    Shader* shader = new Shader();

    shader->myName = GetNameFromPath(aPath);
    shader->myShaderType = aShaderType;
    shader->mySource = ReadFile(aPath);

    return shader;
}

Texture* AssetLoader::LoadTexture(const std::string& aPath)
{
    if (!DoesFileExist(aPath))
    {
        Log::Print(LogType::PROBLEM, "File does not exist: %s", aPath.c_str());
        return nullptr;
    }

    Texture* texture = new Texture();

    texture->myName = GetNameFromPath(aPath);

    unsigned char* image = stbi_load(aPath.c_str(), &texture->myWidth, &texture->myHeight, &texture->myComponents, STBI_default);
    if (!image)
    {
        Log::Print(LogType::PROBLEM, "Failed to load texture: %s", aPath.c_str());
        stbi_image_free(image);
        return nullptr;
    }

    texture->mySource = image;

    Log::Print(LogType::SUCCESS, "Loaded: %s", aPath.c_str());

    return texture;
}

bool AssetLoader::DoesFileExist(const std::string& aPath)
{
    FILE* file;
    errno_t error = fopen_s(&file, aPath.c_str(), "rb");
    if (error != 0)
    {
        return false;
    }

    return true;
}

std::string AssetLoader::ReadFile(const std::string& aPath)
{
    std::string sourceResult;
    std::ifstream sourceStream(aPath, std::ios::in);

    if (!sourceStream.is_open())
    {
        Log::Print(LogType::PROBLEM, "File can't be read: %s", aPath.c_str());
        return "";
    }

    std::stringstream sourceStringStream;
    sourceStringStream << sourceStream.rdbuf();
    sourceResult = sourceStringStream.str();
    sourceStream.close();

    return sourceResult;
}

std::string AssetLoader::GetNameFromPath(const std::string& aPath)
{
    std::size_t lastSlashIndex = aPath.find_last_of("/\\");
    std::size_t lastDotIndex = aPath.find_last_of(".");
    return aPath.substr(lastSlashIndex + 1, aPath.length() - lastDotIndex);
}

Model* AssetLoader::LoadOBJ(const std::string& aPath, const std::string& aFilename, const std::string& aBaseDirectory)
{
    tinyobj::attrib_t attributes;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warning;
    std::string error;

    if (!tinyobj::LoadObj(&attributes, &shapes, &materials, &warning, &error, aPath.c_str(), aBaseDirectory.c_str(), true))
    {
        Log::Print(LogType::PROBLEM, "Failed to load %s", aPath.c_str());

        return nullptr;
    }

    if (!warning.empty())
    {
        Log::Print(LogType::PROBLEM, "%s", warning.c_str());
    }

    if (!error.empty())
    {
        Log::Print(LogType::PROBLEM, "%s", error.c_str());
    }

    Model* model = new Model();
    model->myName = aFilename;

    std::unordered_map<Vertex, unsigned int> uniqueVertices = {};

    for (const tinyobj::shape_t& shape : shapes)
    {
        Mesh mesh;

        for (const tinyobj::index_t& index : shape.mesh.indices)
        {
            Vertex vertex;
            vertex.myPosition.x = attributes.vertices[3 * index.vertex_index + 0];
            vertex.myPosition.y = attributes.vertices[3 * index.vertex_index + 1];
            vertex.myPosition.z = attributes.vertices[3 * index.vertex_index + 2];

            if (attributes.normals.size() > 0)
            {
                vertex.myNormal.x = attributes.normals[3 * index.vertex_index + 0];
                vertex.myNormal.y = attributes.normals[3 * index.vertex_index + 1];
                vertex.myNormal.z = attributes.normals[3 * index.vertex_index + 2];
            }

            if (attributes.texcoords.size() > 0)
            {
                vertex.myTextureCoordinates.x = attributes.texcoords[2 * index.texcoord_index + 0];
                vertex.myTextureCoordinates.y = attributes.texcoords[2 * index.texcoord_index + 1];
            }

            if (uniqueVertices.count(vertex) == 0)
            {
                uniqueVertices[vertex] = static_cast<unsigned int>(mesh.myVertices.size());
                mesh.myVertices.push_back(vertex);
            }

            mesh.myIndices.push_back(uniqueVertices[vertex]);
        }

        model->myMeshes.push_back(mesh);
    }

    for (int i = 0; i < model->myMeshes[0].myIndices.size(); i += 3)
    {
        Vertex& v0 = model->myMeshes[0].myVertices[model->myMeshes[0].myIndices[i]];
        Vertex& v1 = model->myMeshes[0].myVertices[model->myMeshes[0].myIndices[i + 1]];
        Vertex& v2 = model->myMeshes[0].myVertices[model->myMeshes[0].myIndices[i + 2]];
        
        glm::vec3 Edge1 = v1.myPosition - v0.myPosition;
        glm::vec3 Edge2 = v2.myPosition - v0.myPosition;

        float DeltaU1 = v1.myTextureCoordinates.x - v0.myTextureCoordinates.x;
        float DeltaV1 = v1.myTextureCoordinates.y - v0.myTextureCoordinates.y;
        float DeltaU2 = v2.myTextureCoordinates.x - v0.myTextureCoordinates.x;
        float DeltaV2 = v2.myTextureCoordinates.y - v0.myTextureCoordinates.y;

        float f = 1.0f / (DeltaU1 * DeltaV2 - DeltaU2 * DeltaV1);

        glm::vec3 Tangent, Bitangent;

        Tangent.x = f * (DeltaV2 * Edge1.x - DeltaV1 * Edge2.x);
        Tangent.y = f * (DeltaV2 * Edge1.y - DeltaV1 * Edge2.y);
        Tangent.z = f * (DeltaV2 * Edge1.z - DeltaV1 * Edge2.z);

        Bitangent.x = f * (-DeltaU2 * Edge1.x - DeltaU1 * Edge2.x);
        Bitangent.y = f * (-DeltaU2 * Edge1.y - DeltaU1 * Edge2.y);
        Bitangent.z = f * (-DeltaU2 * Edge1.z - DeltaU1 * Edge2.z);

        v0.myTangent += Tangent;
        v1.myTangent += Tangent;
        v2.myTangent += Tangent;
    }

    for (unsigned int i = 0; i < model->myMeshes[0].myVertices.size(); i++)
    {
        model->myMeshes[0].myVertices[i].myTangent = glm::normalize(model->myMeshes[0].myVertices[i].myTangent);
    }

    for (const tinyobj::material_t& material : materials)
    {
        auto addTexturePair = [model, aBaseDirectory](const std::string& aTextureName, TextureType aTextureType)
        {
            if (!aTextureName.empty())
            {
                std::string texturePath = aBaseDirectory + aTextureName;
                model->myTextureMap.insert(std::pair<std::string, TextureType>(texturePath, aTextureType));
            }
        };

        addTexturePair(material.alpha_texname, TextureType::Alpha);
        addTexturePair(material.ambient_texname, TextureType::Ambient);
        addTexturePair(material.bump_texname, TextureType::Bump);
        addTexturePair(material.diffuse_texname, TextureType::Diffuse);
        addTexturePair(material.displacement_texname, TextureType::Displacement);
        addTexturePair(material.reflection_texname, TextureType::Reflection);
        addTexturePair(material.specular_texname, TextureType::Specular);
        addTexturePair(material.specular_highlight_texname, TextureType::SpecularHighlight);
    }

    PrintModelInfo(*model);

    if (model->myMeshes.size() < 1 && model->myMeshes[0].myVertices.size() < 1)
        return nullptr;

    return model;
}

Model* AssetLoader::LoadFBX(const std::string& aPath, const std::string& aFilename)
{
    Assimp::Importer importer;

    unsigned int flags = aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices;
    if (!importer.ValidateFlags(flags))
    {
        Log::Print(LogType::PROBLEM, "Flags are incompatible: %s", aPath.c_str());
        return nullptr;
    }

    const aiScene* scene = importer.ReadFile(aPath.c_str(), flags);
    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        Log::Print(LogType::PROBLEM, "Failed to load %s %s", aPath.c_str(), importer.GetErrorString());
        return nullptr;
    }

    Model* model = new Model();
    model->myName = aFilename;

    for (unsigned int meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex)
    {
        const aiMesh* aiMesh = scene->mMeshes[meshIndex];
        Mesh mesh;

        for (unsigned int vertexIndex = 0; vertexIndex < aiMesh->mNumVertices; vertexIndex++)
        {
            const aiVector3D* position = &(aiMesh->mVertices[vertexIndex]);

            Vertex vertex;
            vertex.myPosition = CastToVec3(*position);

            if (aiMesh->HasTextureCoords(0))
            {
                const aiVector2D& textureCoordinates = aiVector2D(aiMesh->mTextureCoords[0][vertexIndex].x, aiMesh->mTextureCoords[0][vertexIndex].y);
                vertex.myTextureCoordinates = CastToVec2(textureCoordinates);
            }

            mesh.myVertices.push_back(vertex);
        }

        for (unsigned int faceIndex = 0; faceIndex < aiMesh->mNumFaces; ++faceIndex)
        {
            const aiFace& face = aiMesh->mFaces[faceIndex];

            for (unsigned int index = 0; index < face.mNumIndices; ++index)
            {
                mesh.myIndices.push_back(face.mIndices[index]);
            }
        }

        model->myMeshes.push_back(mesh);
    }

    if (scene->HasMaterials())
    {
        for (unsigned int materialIndex = 0; materialIndex < scene->mNumMaterials; ++materialIndex)
        {
            const aiMaterial* material = scene->mMaterials[materialIndex];
            aiString texturePath;

            if (!material->GetTextureCount(aiTextureType_DIFFUSE) || material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) != AI_SUCCESS)
                continue;

            Texture* texture = LoadTexture(texturePath.C_Str());
            if (!texture)
                continue;

            //model->myTextures.push_back(*texture);
        }
    }

    PrintModelInfo(*model);

    if (model->myMeshes.size() < 1 && model->myMeshes[0].myVertices.size() < 1)
        return nullptr;

    return model;
}

void AssetLoader::PrintModelInfo(const Model& aModel)
{
    Log::Print(LogType::SUCCESS, "Loaded %s", aModel.myName.c_str());
    Log::Print(LogType::MESSAGE, "Number of meshes %i", static_cast<int>(aModel.myMeshes.size()));
    //Log::Print(LogType::MESSAGE, "Number of textures %i", static_cast<int>(aModel.myTextures.size()));
    //printf("Number of materials %i\n", static_cast<int>(aModel.myMaterials.size()));

    for (int meshIndex = 0; meshIndex < aModel.myMeshes.size(); ++meshIndex)
    {
        const Mesh& mesh = aModel.myMeshes[meshIndex];
        Log::Print(LogType::MESSAGE, "Number of vertices %i in mesh %i", static_cast<int>(mesh.myVertices.size()), meshIndex);
        Log::Print(LogType::MESSAGE, "Number of indices %i in mesh %i", static_cast<int>(mesh.myIndices.size()), meshIndex);
        Log::Print(LogType::MESSAGE, "Number of triangles %i in mesh %i", static_cast<int>(mesh.myVertices.size() / 3), meshIndex);
    }
}
