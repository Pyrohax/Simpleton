// FRAGMENT SHADER
#version 330 core

in LightData {
	vec3 lightColor;
	vec3 lightPosition;
} inLightData;

in VertexData {
	vec3 normal;
	vec2 textureCoordinates;
} inVertexData;

uniform sampler2D textureSampler;

out vec3 outFragmentColor;

void main()
{
	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * inLightData.lightColor;
	vec3 normalizedNormal = normalize(inVertexData.normal);
	vec3 lightDirection = normalize(inLightData.lightPosition - vec3(1.0, 1.0, 1.0));
	float diffuseFactor = max(dot(normalizedNormal, lightDirection), 0.0);
	vec3 diffuse = diffuseFactor * inLightData.lightColor;
	vec3 result = (ambient + diffuse);

	outFragmentColor = texture(textureSampler, inVertexData.textureCoordinates).rgb * result;
}
