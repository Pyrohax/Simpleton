// VERTEX SHADER
#version 460

layout(location = 0) in vec3 inVertexPositionModelSpace;
layout(location = 1) in vec2 inVertexTextureCoordinates;
layout(location = 2) in vec3 inVertexNormalModelSpace;

out LightData {
	vec3 lightDirectionCameraSpace;
} outLightData;

out VertexData {
	vec3 positionWorldSpace;
	vec3 normalCameraSpace;
	vec3 eyeDirectionCameraSpace;
	vec2 textureCoordinates;
} outVertexData;

uniform float lightIntensity;
uniform vec3 lightPositionWorldSpace;
uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;

void main()
{
	gl_Position = modelViewProjectionMatrix * vec4(inVertexPositionModelSpace, 1.0);

	vec3 vertexPositionCameraSpace = vec3(viewMatrix * modelMatrix * vec4(inVertexPositionModelSpace, 1.0));
	outVertexData.eyeDirectionCameraSpace = vec3(0.0, 0.0, 0.0) - vertexPositionCameraSpace;

	vec3 lightPositionCameraSpace = vec3(viewMatrix * vec4(lightPositionWorldSpace, 1.0));
	outLightData.lightDirectionCameraSpace = lightPositionCameraSpace + outVertexData.eyeDirectionCameraSpace;

	outVertexData.positionWorldSpace = vec3(modelMatrix * vec4(inVertexPositionModelSpace, 1.0));
	outVertexData.normalCameraSpace = vec3(viewMatrix * modelMatrix * vec4(inVertexNormalModelSpace, 1.0));
	outVertexData.textureCoordinates = inVertexTextureCoordinates;
}
