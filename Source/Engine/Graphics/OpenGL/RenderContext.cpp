#include "RenderContext.h"

#include "ShaderLibrary.h"
#include "GLError.h"
#include "../../World/Camera.h"
#include "../../Core/InputManager.h"
#include "../Mesh.h"
#include "../Vertex.h"
#include "../Texture.h"
#include "TextureLibrary.h"
#include "../Light.h"

#include <cstddef>

RenderContext::RenderContext()
	: myLight(nullptr)
{
}

RenderContext::~RenderContext()
{
}

void RenderContext::PrintDebugInfo()
{
	Log::Logger::Print(Log::Severity::Message, Log::Category::Rendering, "OpenGL %s", glGetString(GL_VERSION));
	Log::Logger::Print(Log::Severity::Message, Log::Category::Rendering, "GLSL %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void RenderContext::CreateLight()
{
	myLight = new Light();
	myLight->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	myLight->SetPosition(glm::vec3(-5.f, -2.5f, 7.5f));
}

void RenderContext::Initialize()
{
	if (!gladLoadGL())
	{
		Log::Logger::Print(Log::Severity::Error, Log::Category::Rendering ,"Failed to load GLAD, because GL_VERSION returned NULL or function prototypes could not be loaded");
		return;
	}

	PrintDebugInfo();

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageControl(GL_DEBUG_SOURCE_API, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_FALSE);
	glDebugMessageCallback(ErrorCallback, nullptr);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	CheckGLError();

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
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(offsetof(Vertex, myPosition)));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(offsetof(Vertex, myTextureCoordinates)));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(offsetof(Vertex, myNormal)));

		glBindVertexArray(0);
		
		CheckGLError();
	}
}

void RenderContext::Render(const std::vector<Model>& aModels, const TextureLibrary& aTextureLibrary, ShaderLibrary& aShaderLibrary, Camera& aCamera, int aWidth, int aHeight, float aDeltaTime)
{
	aCamera.Update(aDeltaTime);

	for (const Model& model : aModels)
	{
		glm::mat4 modelViewProjection = aCamera.GetProjectionMatrix()  * aCamera.GetViewMatrix() * model.myModelMatrix;
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

	delete myLight;
}
