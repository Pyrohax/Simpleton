#include "AssetLoader.h"

#include "../Core/Logger.h"
#include "../Core/Engine.h"
#include "../Graphics/Vertex.h"
#include "../Graphics/Texture.h"
#include "../Graphics/Model.h"
#include "../Graphics/Mesh.h"
#include "../Graphics/Shader.h"
#include "../Graphics/VectorUtilities.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_NOEXCEPTION
#define JSON_NOEXCEPTION
#include <tiny_gltf.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image.h>
#include <fstream>
#include <sstream>

#include <glm/vec3.hpp>
#include <glm/gtx/functions.hpp>

#include <algorithm>
#include <unordered_map>
#include <filesystem>

AssetLoader::AssetLoader()
{
    myWorkingDirectory = std::filesystem::current_path().string().c_str();
    Log::Logger::Print(Log::Severity::Message, Log::Category::Asset, "Current working directory: %s", myWorkingDirectory.c_str());
}

AssetLoader::~AssetLoader()
{
}

Model* AssetLoader::LoadModel(const std::string& aPath)
{
    if (!DoesFileExist(aPath))
    {
        Log::Logger::Print(Log::Severity::Error, Log::Category::Asset, "File does not exist: %s", aPath.c_str());
        return nullptr;
    }

    const std::string& fileExtension = GetExtensionFromPath(aPath);
    if (fileExtension == "obj")
    {
       return LoadOBJ(aPath);
    }
    else if (fileExtension == "fbx")
    {
        return LoadFBX(aPath);
    }

    return nullptr;
}

Shader* AssetLoader::LoadShader(const std::string& aPath, ShaderType aShaderType)
{
    if (!DoesFileExist(aPath))
    {
        Log::Logger::Print(Log::Severity::Error, Log::Category::Asset, "File does not exist: %s", aPath.c_str());
        return nullptr;
    }

    Shader* shader = new Shader();

    shader->myName = GetNameFromPath(aPath);
    shader->myFileExtension = GetExtensionFromPath(aPath);
    shader->myShaderType = aShaderType;
    shader->mySource = ReadFile(aPath);

    return shader;
}

Texture* AssetLoader::LoadTexture(const std::string& aPath)
{
    if (!DoesFileExist(aPath))
    {
        Log::Logger::Print(Log::Severity::Error, Log::Category::Asset, "File does not exist: %s", aPath.c_str());
        return nullptr;
    }

    Texture* texture = new Texture();

    texture->myName = GetNameFromPath(aPath);
    texture->myFileExtension = GetExtensionFromPath(aPath);

    unsigned char* image = stbi_load(aPath.c_str(), &texture->myWidth, &texture->myHeight, &texture->myComponents, STBI_default);
    if (!image)
    {
        Log::Logger::Print(Log::Severity::Error, Log::Category::Asset, "Failed to load texture: %s", aPath.c_str());
        stbi_image_free(image);
        return nullptr;
    }

    texture->mySource = image;

    Log::Logger::Print(Log::Severity::Success, Log::Category::Asset, "Loaded: %s", aPath.c_str());

    return texture;
}

bool AssetLoader::DoesFileExist(const std::string& aPath) const
{
    std::filesystem::file_status fileStatus;
    std::filesystem::path test = std::filesystem::current_path();
    return std::filesystem::status_known(fileStatus) ? std::filesystem::exists(fileStatus) : std::filesystem::exists(aPath);
}

std::string AssetLoader::ReadFile(const std::string& aPath)
{
    std::string sourceResult;
    std::ifstream sourceStream(aPath, std::ios::in);

    if (!sourceStream.is_open())
    {
        Log::Logger::Print(Log::Severity::Error, Log::Category::Asset, "File can't be read: %s", aPath.c_str());
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
    const std::size_t& nameStartIndex = aPath.find_last_of("/\\") + 1;
    const std::size_t& extensionStartIndex = aPath.find_last_of(".");
    return aPath.substr(nameStartIndex, aPath.length() - nameStartIndex - (aPath.length() - extensionStartIndex));
}

std::string AssetLoader::GetExtensionFromPath(const std::string& aPath)
{
    const std::size_t& extensionStartIndex = aPath.find_last_of(".") + 1;
    return aPath.substr(extensionStartIndex, aPath.length() - extensionStartIndex);
}

std::string AssetLoader::GetDirectoryFromPath(const std::string& aPath)
{
    std::size_t lastSlashIndex = aPath.find_last_of("/\\");
    return aPath.substr(0, lastSlashIndex + 1);
}

Model* AssetLoader::LoadOBJ(const std::string& aPath)
{
    tinyobj::attrib_t attributes;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warning;
    std::string error;

    const std::string& fileName = GetNameFromPath(aPath);
    const std::string& directory = GetDirectoryFromPath(aPath);
    const std::string& fileExtension = GetExtensionFromPath(aPath);

    if (!tinyobj::LoadObj(&attributes, &shapes, &materials, &warning, &error, aPath.c_str(), directory.c_str(), true))
    {
        Log::Logger::Print(Log::Severity::Error, Log::Category::Asset, "Failed to load %s", aPath.c_str());

        return nullptr;
    }

    if (!warning.empty())
    {
        Log::Logger::Print(Log::Severity::Error, Log::Category::Asset, "%s", warning.c_str());
    }

    if (!error.empty())
    {
        Log::Logger::Print(Log::Severity::Error, Log::Category::Asset, "%s", error.c_str());
    }

    Model* model = new Model();
    model->myName = fileName;
    model->myFileExtension = fileExtension;

    std::unordered_map<Vertex, unsigned int> uniqueVertices = {};

    for (const tinyobj::shape_t& shape : shapes)
    {
        Mesh mesh;

        for (const tinyobj::index_t& index : shape.mesh.indices)
        {
            Vertex vertex;
            size_t vertexIndexStride = 3 * static_cast<size_t>(index.vertex_index);
            vertex.myPosition.x = attributes.vertices[vertexIndexStride + 0];
            vertex.myPosition.y = attributes.vertices[vertexIndexStride + 1];
            vertex.myPosition.z = attributes.vertices[vertexIndexStride + 2];

            if (attributes.normals.size() > 0)
            {
                vertex.myNormal.x = attributes.normals[vertexIndexStride + 0];
                vertex.myNormal.y = attributes.normals[vertexIndexStride + 1];
                vertex.myNormal.z = attributes.normals[vertexIndexStride + 2];
            }

            if (attributes.texcoords.size() > 0)
            {
                size_t textureCoordinatesIndexStride = 2 * static_cast<size_t>(index.texcoord_index);
                vertex.myTextureCoordinates.x = attributes.texcoords[textureCoordinatesIndexStride + 0];
                vertex.myTextureCoordinates.y = attributes.texcoords[textureCoordinatesIndexStride + 1];
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

    for (const tinyobj::material_t& material : materials)
    {
        auto addTexturePair = [model, directory](const std::string& aTextureName, TextureType aTextureType)
        {
            if (!aTextureName.empty())
            {
                std::string texturePath = directory + aTextureName;
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

Model* AssetLoader::LoadFBX(const std::string& aPath)
{
    Assimp::Importer importer;

    unsigned int flags = aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices;
    if (!importer.ValidateFlags(flags))
    {
        Log::Logger::Print(Log::Severity::Error, Log::Category::Asset, "Flags are incompatible: %s", aPath.c_str());
        return nullptr;
    }

    const aiScene* scene = importer.ReadFile(aPath.c_str(), flags);
    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        Log::Logger::Print(Log::Severity::Error, Log::Category::Asset, "Failed to load %s %s", aPath.c_str(), importer.GetErrorString());
        return nullptr;
    }

    const std::string& fileName = GetNameFromPath(aPath);
    const std::string& fileExtension = GetExtensionFromPath(aPath);

    Model* model = new Model();
    model->myName = fileName;
    model->myFileExtension = fileExtension;

    for (unsigned int meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex)
    {
        const aiMesh* aiMesh = scene->mMeshes[meshIndex];
        Mesh mesh;

        for (unsigned int vertexIndex = 0; vertexIndex < aiMesh->mNumVertices; vertexIndex++)
        {
            Vertex vertex;

            const aiVector3D* position = &(aiMesh->mVertices[vertexIndex]);
            vertex.myPosition = CastToVec3(*position);

            const aiVector3D* normal = &(aiMesh->mVertices[vertexIndex]);
            vertex.myNormal = CastToVec3(*normal);

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

Model* AssetLoader::LoadGLTF(const std::string& aPath)
{
    tinygltf::Model tinyGLTFModel;
    tinygltf::TinyGLTF loader;
    std::string err;
    std::string warn;

    bool res = loader.LoadASCIIFromFile(&tinyGLTFModel, &err, &warn, aPath);
    if (!warn.empty())
    {
        Log::Logger::Print(Log::Severity::Error, Log::Category::Asset, "Failed to load %s %s", aPath.c_str(), warn);
        return nullptr;
    }

    if (!err.empty())
    {
        Log::Logger::Print(Log::Severity::Error, Log::Category::Asset, "Failed to load %s %s", aPath.c_str(), err);
        return nullptr;
    }

    if (!res)
    {
        Log::Logger::Print(Log::Severity::Error, Log::Category::Asset, "Failed to load %s %s", aPath.c_str());
        return nullptr;
    }

    const std::string& fileName = GetNameFromPath(aPath);
    const std::string& directory = GetDirectoryFromPath(aPath);
    const std::string& fileExtension = GetExtensionFromPath(aPath);

    Model* model = new Model();
    model->myName = fileName;
    model->myFileExtension = fileExtension;

    for (const tinygltf::Mesh& mesh : tinyGLTFModel.meshes)
    {
        for (const tinygltf::Primitive primitive : mesh.primitives)
        {
            tinygltf::Accessor indexAccessor = tinyGLTFModel.accessors[primitive.indices];

            for (auto& attrib : primitive.attributes)
            {
                tinygltf::Accessor accessor = tinyGLTFModel.accessors[attrib.second];
                int byteStride = accessor.ByteStride(tinyGLTFModel.bufferViews[accessor.bufferView]);
                //glBindBuffer(GL_ARRAY_BUFFER, vbos[accessor.bufferView]);

                int size = 1;
                if (accessor.type != TINYGLTF_TYPE_SCALAR)
                {
                    size = accessor.type;
                }

                int vaa = -1;
                if (attrib.first.compare("POSITION") == 0) vaa = 0;
                if (attrib.first.compare("NORMAL") == 0) vaa = 1;
                if (attrib.first.compare("TEXCOORD_0") == 0) vaa = 2;
                if (vaa > -1)
                {
                    /*glEnableVertexAttribArray(vaa);
                    glVertexAttribPointer(vaa, size, accessor.componentType,
                                          accessor.normalized ? true : false,
                                          byteStride, BUFFER_OFFSET(accessor.byteOffset));*/
                }
            }
        }
    }

    if (tinyGLTFModel.textures.size() > 0)
    {
        // fixme: Use material's baseColor
        tinygltf::Texture& tex = tinyGLTFModel.textures[0];

        if (tex.source > -1)
        {
            tinygltf::Image& image = tinyGLTFModel.images[tex.source];
            Texture* texture = new Texture();
            texture->mySource = &image.image.at(0);
            texture->myHeight = image.height;
            texture->myWidth = image.width;
            model->myTextures.push_back(texture);
        }
    }

    return model;
}

void AssetLoader::PrintModelInfo(const Model& aModel)
{
    Log::Logger::Print(Log::Severity::Success, Log::Category::Asset, "Loaded %s", aModel.myName.c_str());
    Log::Logger::Print(Log::Severity::Message, Log::Category::Asset, "Number of meshes %i", static_cast<int>(aModel.myMeshes.size()));
    //Log::Logger::Print(Log::Severity::Message, "Number of textures %i", static_cast<int>(aModel.myTextures.size()));
    //printf("Number of materials %i\n", static_cast<int>(aModel.myMaterials.size()));

    for (int meshIndex = 0; meshIndex < aModel.myMeshes.size(); ++meshIndex)
    {
        const Mesh& mesh = aModel.myMeshes[meshIndex];
        Log::Logger::Print(Log::Severity::Message, Log::Category::Asset, "Number of vertices %i in mesh %i", static_cast<int>(mesh.myVertices.size()), meshIndex);
        Log::Logger::Print(Log::Severity::Message, Log::Category::Asset, "Number of indices %i in mesh %i", static_cast<int>(mesh.myIndices.size()), meshIndex);
        Log::Logger::Print(Log::Severity::Message, Log::Category::Asset, "Number of triangles %i in mesh %i", static_cast<int>(mesh.myVertices.size() / 3), meshIndex);
    }
}
