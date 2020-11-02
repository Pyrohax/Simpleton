// VERTEX SHADER
#version 330 core

layout(location = 0) in vec3 inVertexPositionModelSpace;
layout(location = 1) in vec2 inVertexUVs;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec3 inTangent;

out LightData {
	vec3 lightColor;
	vec3 lightPosition;
} outLightData;

out VertexData {
	vec3 normal;
	vec2 textureCoordinates;
} outVertexData;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelMatrix;
uniform vec3 lightColor;
uniform vec3 lightPosition;

void main()
{
	gl_Position = modelViewProjectionMatrix * vec4(inVertexPositionModelSpace, 1.0f);

	outVertexData.textureCoordinates = inVertexUVs;
	outLightData.lightColor = lightColor;
	outVertexData.normal = mat3(transpose(inverse(modelMatrix))) * inNormal;
	outLightData.lightPosition = lightPosition;
}
