#include "RenderContext.h"

#include "ShaderLibrary.h"
#include "GLError.h"
#include "Camera.h"
#include "Model.h"
#include "Mesh.h"
#include "Vertex.h"
#include "Texture.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <cstddef>

RenderContext::RenderContext()
	: myCamera(nullptr)
{
	if (!gladLoadGL())
	{
		printf("Failed to load GLAD, because GL_VERSION returned NULL or function prototypes could not be loaded.\n");
		return;
	}

	PrintDebugInfo();

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
}

void RenderContext::PrintDebugInfo()
{
	printf("OpenGL %s\n", glGetString(GL_VERSION));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void RenderContext::CreateCamera()
{
	myCamera = new Camera();
	myCamera->myProjection = glm::perspective(glm::radians(45.0f), 1240.0f / 720.0f, 0.1f, 100.0f);
	myCamera->myView = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}

void RenderContext::CreateBuffers(std::vector<Model>& aModels)
{
	for (Model& model : aModels)
	{
		glGenVertexArrays(1, &model.myVertexArrayObject);
		glBindVertexArray(model.myVertexArrayObject);

		glGenBuffers(1, &model.myVertexBufferObject);
		glBindBuffer(GL_ARRAY_BUFFER, model.myVertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, model.myMeshes[0].myVertices.size() * sizeof(Vertex), &model.myMeshes[0].myVertices.front(), GL_STATIC_DRAW);

		glGenBuffers(1, &model.myElementBufferObject);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.myElementBufferObject);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.myMeshes[0].myIndices.size() * sizeof(unsigned int), &model.myMeshes[0].myIndices.front(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, myPosition));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, myTextureCoordinates));

		glBindVertexArray(0);
		
		CheckGLError();
	}
}

void RenderContext::Render(const std::vector<Model>& aModels, const ShaderLibrary& aShaderLibrary, int aWidth, int aHeight)
{
	for (const Model& model : aModels)
	{
		glm::mat4 mvp = myCamera->myProjection * myCamera->myView * model.myModelMatrix;

		GLuint MatrixID = glGetUniformLocation(aShaderLibrary.GetProgramID(), "MVP");

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

		glViewport(0, 0, aWidth, aHeight);
		glClearColor(0.7f, 0.9f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (model.myTextures.size())
		{
			glActiveTexture(GL_TEXTURE0 + model.myTextureUnit);
			glUniform1i(glGetUniformLocation(aShaderLibrary.GetProgramID(), "textureSampler"), model.myTextureUnit);
			glBindTexture(GL_TEXTURE_2D, model.myTextures[0].myID);
		}

		glBindVertexArray(model.myVertexArrayObject);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.myElementBufferObject);
		glDrawElements(GL_TRIANGLES, model.myMeshes[0].myIndices.size(), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);

		CheckGLError();
	}
}

void RenderContext::Destroy(const std::vector<Model>& aModels)
{
	glBindVertexArray(0);

	for (const Model& model : aModels)
	{
		glDeleteVertexArrays(1, &model.myVertexArrayObject);
		glDeleteBuffers(1, &model.myVertexBufferObject);
	}
}
