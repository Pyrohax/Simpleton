// FRAGMENT SHADER
#version 460

in LightData {
	vec3 lightDirectionCameraSpace;
} inLightData;

in VertexData {
	vec3 positionWorldSpace;
	vec3 normalCameraSpace;
	vec3 eyeDirectionCameraSpace;
	vec2 textureCoordinates;
} inVertexData;

uniform sampler2D textureSampler;
uniform float lightIntensity;
uniform vec3 lightColor;
uniform vec3 lightPositionWorldSpace;

out vec3 outFragmentColor;

void main()
{
	vec3 materialDiffuseColor = texture(textureSampler, inVertexData.textureCoordinates).rgb;
	vec3 materialAmbientColor = vec3(0.1, 0.1, 0.1) * materialDiffuseColor;
	vec3 materialSpecularColor = vec3(0.3, 0.3, 0.3);

	float distance = length(lightPositionWorldSpace - inVertexData.positionWorldSpace);

	vec3 normal = normalize(inVertexData.normalCameraSpace);
	vec3 lightDirection = normalize(inLightData.lightDirectionCameraSpace);
	float cosTheta = clamp(dot(normal, lightDirection), 0.0, 1.0);

	vec3 eyeDirection = normalize(inVertexData.eyeDirectionCameraSpace);
	vec3 reflection = reflect(-lightDirection, normal);
	float cosAlpha = clamp(dot(eyeDirection, reflection), 0.0, 1.0);

	outFragmentColor = materialAmbientColor + materialDiffuseColor * lightColor * lightIntensity * cosTheta / (distance * distance) + materialSpecularColor * lightColor * lightIntensity * pow(cosAlpha,5) / (distance * distance);
}
