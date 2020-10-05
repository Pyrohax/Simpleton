#include "Model.h"

#include "Texture.h"

Model::Model()
    : myModelMatrix(1.0f)
    , myPosition(0.0f)
    , myName("")
    , myVertexArrayObject(0)
    , myVertexBufferObject(0)
    , myColorBufferObject(0)
    , myElementBufferObject(0)
{
}

Model::~Model()
{
    myMeshes.clear();
}
