#include "RenderContext.h"
#include "ShaderLibrary.h"
#include "GLError.h"
#include "Camera.h"
#include "Model.h"
#include "Vertex.h"
#include "Texture.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <cstddef>

RenderContext::RenderContext()
	: myShaderLibrary(nullptr)
	, myCamera(nullptr)
	, myModel(nullptr)
{
	if (!gladLoadGL())
	{
		printf("Failed to load GLAD\n");
		return;
	}

	PrintDebugInfo();
	LoadModel();
	LoadShaders();

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(ErrorCallback, nullptr);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	CheckGLError();

	CreateCamera();
}

RenderContext::~RenderContext()
{
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &myModel->myVertexArrayObject);
	glDeleteBuffers(1, &myModel->myVertexBufferObject);
}

void RenderContext::PrintDebugInfo()
{
	printf("OpenGL %s\n", glGetString(GL_VERSION));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void RenderContext::LoadModel()
{
	myModel = new Model("../Data/Models/Cube/Cube.obj");

	if (!myModel->GetMeshes().size())
		return;

	if (!myModel->GetMeshes()[0].myVertices.size() || !myModel->GetMeshes()[0].myIndices.size())
		return;

	glGenVertexArrays(1, &myModel->myVertexArrayObject);
	glBindVertexArray(myModel->myVertexArrayObject);

	glGenBuffers(1, &myModel->myVertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, myModel->myVertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, myModel->GetMeshes()[0].myVertices.size() * sizeof(Vertex), &myModel->GetMeshes()[0].myVertices.front(), GL_STATIC_DRAW);

	glGenBuffers(1, &myModel->myElementBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myModel->myElementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, myModel->GetMeshes()[0].myIndices.size() * sizeof(unsigned int), &myModel->GetMeshes()[0].myIndices.front(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, myPosition));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, myTextureCoordinates));

	glBindVertexArray(0);

	CheckGLError();
}

void RenderContext::LoadShaders()
{
	myShaderLibrary = new ShaderLibrary();

	CheckGLError();
}

void RenderContext::CreateCamera()
{
	myCamera = new Camera();
	myCamera->myProjection = glm::perspective(glm::radians(45.0f), 1240.0f / 720.0f, 0.1f, 100.0f);
	myCamera->myView = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}

void RenderContext::Render(int aWidth, int aHeight)
{
	myShaderLibrary->BindShaders();

	glm::mat4 mvp = myCamera->myProjection * myCamera->myView * myModel->GetModelMatrix();

	GLuint MatrixID = glGetUniformLocation(myShaderLibrary->GetProgramID(), "MVP");

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

	glViewport(0, 0, aWidth, aHeight);
	glClearColor(0.7f, 0.9f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (!myModel->GetMeshes().size())
		return;

	if (!myModel->GetMeshes()[0].myVertices.size() || !myModel->GetMeshes()[0].myIndices.size())
		return;

	if (myModel->GetTextures().size())
	{
		glActiveTexture(GL_TEXTURE0 + myModel->myTextureUnit);
		glUniform1i(glGetUniformLocation(myShaderLibrary->GetProgramID(), "textureSampler"), myModel->myTextureUnit);
		glBindTexture(GL_TEXTURE_2D, myModel->GetTextures()[0]->GetID());
	}

	glBindVertexArray(myModel->myVertexArrayObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myModel->myElementBufferObject);
	glDrawElements(GL_TRIANGLES, myModel->GetMeshes()[0].myIndices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

	CheckGLError();
}
