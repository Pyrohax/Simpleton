#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUVs;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec3 aTangent;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

out vec2 textureCoordinates;
out vec3 objectColorOut;
out vec3 lightColorOut;
out vec3 Normal;
out vec3 lightPosOut;

uniform mat4 MVP;
uniform mat4 Model;

void main()
{
	gl_Position = MVP * vec4(vertexPosition_modelspace, 1.0f);

	textureCoordinates = vertexUVs;
	objectColorOut = objectColor;
	lightColorOut = lightColor;
	Normal = mat3(transpose(inverse(Model))) * aNormal;
	lightPosOut = lightPos;
}
