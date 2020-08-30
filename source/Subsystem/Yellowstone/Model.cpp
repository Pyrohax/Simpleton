#include "Model.h"
#include "Vertex.h"
#include "GLError.h"
#include "Texture.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <algorithm>
#include <unordered_map>

Model::Model(const std::string aPath)
    : myModelMatrix(1.0f)
    , myPosition(0.0f)
    , myVertexArrayObject(0)
    , myVertexBufferObject(0)
    , myTextureUnit(0)
{
    if (!DoesFileExist(aPath))
    {
        printf("%s does not exist\n", aPath.c_str());
        return;
    }

    std::size_t lastSlashIndex = aPath.find_last_of("/\\");
    std::size_t lastDotIndex = aPath.find_last_of(".");
    std::string baseDirectory = aPath.substr(0, lastSlashIndex + 1);
    std::string file = aPath.substr(lastSlashIndex + 1, aPath.length() - lastDotIndex);
    std::string extension = aPath.substr(lastDotIndex + 1, aPath.length());

    if (extension == "obj")
    {
        LoadOBJ(aPath, baseDirectory);
    }
    else if (extension == "fbx")
    {
        LoadFBX(aPath);
    }
}

Model::~Model()
{
    myMeshes.clear();
}

bool Model::DoesFileExist(const std::string& aPath)
{
    FILE* file;
    errno_t error = fopen_s(&file, aPath.c_str(), "rb");
    if (error != 0)
    {
        return false;
    }

    return true;
}

void Model::LoadOBJ(const std::string aPath, const std::string aBaseDirectory)
{
    tinyobj::attrib_t attributes;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warning;
    std::string error;

    if (!tinyobj::LoadObj(&attributes, &shapes, &materials, &warning, &error, aPath.c_str(), aBaseDirectory.c_str(), true))
    {
        printf("Failed to load %s\n", aPath.c_str());
        return;
    }

    if (!warning.empty())
    {
        printf("%s\n", warning.c_str());
    }

    if (!error.empty())
    {
        printf("%s\n", error.c_str());
    }

    std::unordered_map<Vertex, unsigned int> uniqueVertices = {};

    for (const tinyobj::shape_t shape : shapes)
    {
        Mesh mesh;

        for (const tinyobj::index_t& index : shape.mesh.indices)
        {
            Vertex vertex;
            vertex.myPosition.x = attributes.vertices[3 * index.vertex_index + 0];
            vertex.myPosition.y = attributes.vertices[3 * index.vertex_index + 1];
            vertex.myPosition.z = attributes.vertices[3 * index.vertex_index + 2];

            if (attributes.texcoords.size())
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

        myMeshes.push_back(mesh);
    }

    for (int materialIndex = 0; materialIndex < materials.size(); ++materialIndex)
    {
        const tinyobj::material_t& material = materials[materialIndex];

        if (!material.diffuse_texname.length())
            break;

        std::string texturePath = aBaseDirectory + material.diffuse_texname;

        if (!DoesFileExist(texturePath))
            break;

        Texture* texture = new Texture(texturePath);
        myTextures.push_back(texture);
    }

    printf("Loaded %s\n", aPath.c_str());
    printf("Number of meshes %i\n", static_cast<int>(myMeshes.size()));
    printf("Number of materials %i\n", static_cast<int>(materials.size()));
    printf("Number of textures %i\n", static_cast<int>(myTextures.size()));

    for (int meshIndex = 0; meshIndex < myMeshes.size(); ++meshIndex)
    {
        printf("Number of vertices %i in mesh %i\n", static_cast<int>(myMeshes[meshIndex].myVertices.size()), meshIndex);
        printf("Number of indices %i in mesh %i\n", static_cast<int>(myMeshes[meshIndex].myIndices.size()), meshIndex);
        printf("Number of triangles %i in mesh %i\n", static_cast<int>(myMeshes[meshIndex].myVertices.size() / 3), meshIndex);
    }
}

void Model::LoadFBX(const std::string aPath)
{
    Assimp::Importer importer;

    unsigned int flags = aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices;
    if (!importer.ValidateFlags(flags))
    {
        printf("Flags are incompatible\n");
    }

    const aiScene* scene = importer.ReadFile(aPath.c_str(), flags);
    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        printf("Failed to load %s %s\n", aPath.c_str(), importer.GetErrorString());
        return;
    }

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

        myMeshes.push_back(mesh);
    }

    if (scene->HasMaterials())
    {
        for (unsigned int materialIndex = 0; materialIndex < scene->mNumMaterials; ++materialIndex)
        {
            const aiMaterial* material = scene->mMaterials[materialIndex];
            aiString texturePath;

            if (!material->GetTextureCount(aiTextureType_DIFFUSE) || material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) != AI_SUCCESS)
                break;

            if (!DoesFileExist(texturePath.C_Str()))
                break;

            Texture* texture = new Texture(texturePath.C_Str());
            myTextures.push_back(texture);
        }
    }

    printf("Loaded %s\n", aPath.c_str());
    printf("Number of meshes %i\n", static_cast<int>(myMeshes.size()));
    printf("Number of materials %i\n", static_cast<int>(scene->mNumMaterials));
    printf("Number of textures %i\n", static_cast<int>(myTextures.size()));

    for (int meshIndex = 0; meshIndex < myMeshes.size(); ++meshIndex)
    {
        printf("Number of vertices %i in mesh %i\n", static_cast<int>(myMeshes[meshIndex].myVertices.size()), meshIndex);
        printf("Number of indices %i in mesh %i\n", static_cast<int>(myMeshes[meshIndex].myIndices.size()), meshIndex);
        printf("Number of triangles %i in mesh %i\n", static_cast<int>(myMeshes[meshIndex].myVertices.size() / 3), meshIndex);
    }
}
