#include "RenderContext.h"

#include "ShaderLibrary.h"
#include "GLError.h"
#include "Camera.h"
#include "Model.h"
#include "Mesh.h"
#include "Vertex.h"
#include "Texture.h"
#include "InputManager.h"
#include "TextureLibrary.h"
#include "Light.h"

#include <cstddef>

RenderContext::RenderContext()
	: myCamera(nullptr)
	, myLight(nullptr)
{
}

RenderContext::~RenderContext()
{
}

void RenderContext::PrintDebugInfo()
{
	Log::Print(LogType::MESSAGE, "OpenGL %s", glGetString(GL_VERSION));
	Log::Print(LogType::MESSAGE, "GLSL %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void RenderContext::CreateCamera()
{
	myCamera = new Camera();
}

void RenderContext::CreateLight()
{
	myLight = new Light();
	myLight->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
}

void RenderContext::Initialize()
{
	if (!gladLoadGL())
	{
		Log::Print(LogType::PROBLEM, "Failed to load GLAD, because GL_VERSION returned NULL or function prototypes could not be loaded");
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
	CreateLight();
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

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, myNormal));

		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, myTangent));

		glBindVertexArray(0);
		
		CheckGLError();
	}
}

void RenderContext::Render(const std::vector<Model>& aModels, const TextureLibrary& aTextureLibrary, ShaderLibrary& aShaderLibrary, int aWidth, int aHeight, double aDeltaTime)
{
	myCamera->Update(aDeltaTime);

	for (const Model& model : aModels)
	{
		glm::mat4 modelViewProjection = myCamera->GetProjectionMatrix()  * myCamera->GetViewMatrix() * model.myModelMatrix;
		aShaderLibrary.SetMatrix4Float("modelViewProjectionMatrix", modelViewProjection);
		aShaderLibrary.SetMatrix4Float("modelMatrix", model.myModelMatrix);

		glViewport(0, 0, aWidth, aHeight);
		glClearColor(0.7f, 0.9f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (aTextureLibrary.myTextures.size() > 0)
		{
			const unsigned int textureID = aTextureLibrary.myTextures[0].myID;
			glActiveTexture(GL_TEXTURE0 + textureID);
			aShaderLibrary.SetInt("textureSampler", textureID);
			glBindTexture(GL_TEXTURE_2D, textureID);
		}

		aShaderLibrary.SetVector3Float("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
		aShaderLibrary.SetVector3Float("lightColor", myLight->GetColor());
		aShaderLibrary.SetVector3Float("lightPosition", myLight->GetPosition());

		glBindVertexArray(model.myVertexArrayObject);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.myElementBufferObject);
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(model.myMeshes[0].myIndices.size()), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

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
