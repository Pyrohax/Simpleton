#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTextureCoordinates;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec3 aTangent;

out vec2 textureCoordinates;
out vec4 lightSpacePosition;
out vec3 normal;
out vec3 worldPosition;
out vec3 tangent;

uniform mat4 gWVP;
uniform mat4 gLightWVP;
uniform mat4 gWorld;

void main()
{
	gl_Position = gWVP * vec4(aPosition, 1.0f);
	textureCoordinates = textureCoordinates;
	lightSpacePosition = gLightWVP * vec4(aPosition, 1.0f);
	normal = (gWorld * vec4(aNormal, 0.0)).xyz;
    tangent = (gWorld * vec4(aTangent, 0.0)).xyz;
    worldPosition = (gWorld * vec4(aPosition, 1.0)).xyz;
}