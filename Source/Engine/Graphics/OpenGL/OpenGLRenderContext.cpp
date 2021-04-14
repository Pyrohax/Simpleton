#include "OpenGLRenderContext.h"

#include "../../Core/InputManager.h"
#include "../../World/Entity.h"
#include "../Mesh.h"
#include "../Texture.h"
#include "../Vertex.h"
#include "OpenGLError.h"
#include "OpenGLShaderLibrary.h"
#include "OpenGLTextureLibrary.h"
#include "../../World/LightingComponent.h"
#include "../../World/TransformComponent.h"
#include "../../World/CameraComponent.h"

#include <cstddef>

OpenGLRenderContext::OpenGLRenderContext() : RenderContext()
{
}

OpenGLRenderContext::~OpenGLRenderContext()
{
}

void OpenGLRenderContext::PrintDebugInfo()
{
	Log::Logger::Print(Log::Severity::Message, Log::Category::Rendering, "OpenGL %s", glGetString(GL_VERSION));
	Log::Logger::Print(Log::Severity::Message, Log::Category::Rendering, "GLSL %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void OpenGLRenderContext::Initialize()
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
}

void OpenGLRenderContext::CreateBuffers(std::vector<Model>& aModels)
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

void OpenGLRenderContext::Render(const std::vector<Model>& aModels, const TextureLibrary& aTextureLibrary, ShaderLibrary& aShaderLibrary, Entity& aCamera, const Entity& aLighting, int aWidth, int aHeight, float aDeltaTime)
{
	CameraComponent* cameraComponent = aCamera.GetComponent<CameraComponent>();
	cameraComponent->Update(aDeltaTime);

	glViewport(0, 0, aWidth, aHeight);
	glClearColor(0.7f, 0.9f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	const int shaderCount = static_cast<int>(aShaderLibrary.GetShaders().size());
	if (shaderCount > 0)
	{
		aShaderLibrary.BindShaders();
		aShaderLibrary.SetVector3Float("lightColor", aLighting.GetComponent<LightingComponent>()->GetColor());
		aShaderLibrary.SetVector3Float("lightPositionWorldSpace", aLighting.GetComponent<TransformComponent>()->GetPosition());
		aShaderLibrary.SetFloat("lightIntensity", 10.0f);
	}

	for (const Model& model : aModels)
	{
		if (shaderCount > 0)
		{
			const glm::mat4x4& viewMatrix = cameraComponent->GetViewMatrix();
			const glm::mat4x4& modelMatrix = model.myModelMatrix;
			const glm::mat4x4 modelViewProjectionMatrix = cameraComponent->GetProjectionMatrix() * viewMatrix * modelMatrix;
			aShaderLibrary.SetMatrix4Float("modelViewProjectionMatrix", modelViewProjectionMatrix);
			aShaderLibrary.SetMatrix4Float("modelMatrix", modelMatrix);
			aShaderLibrary.SetMatrix4Float("viewMatrix", viewMatrix);
		}

		if (aTextureLibrary.myTextures.size() > 0)
		{
			const unsigned int textureID = aTextureLibrary.myTextures[0].myID;
			glActiveTexture(GL_TEXTURE0 + textureID);
			aShaderLibrary.SetInt("textureSampler", textureID);
			glBindTexture(GL_TEXTURE_2D, textureID);
		}

		glBindVertexArray(model.myVertexArrayObject);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.myElementBufferObject);
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(model.myMeshes[0].myIndices.size()), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	if (shaderCount > 0)
	{
		aShaderLibrary.UnbindShaders();
	}

	CheckGLError();
}

void OpenGLRenderContext::Destroy(const std::vector<Model>& aModels)
{
	glBindVertexArray(0);

	for (const Model& model : aModels)
	{
		glDeleteVertexArrays(1, &model.myVertexArrayObject);
		glDeleteBuffers(1, &model.myVertexBufferObject);
	}
}
