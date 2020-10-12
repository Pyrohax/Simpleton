#version 330 core

in vec2 textureCoordinates;
in vec3 objectColorOut;
in vec3 lightColorOut;
in vec3 Normal;
in vec3 lightPosOut;

out vec3 color;

uniform sampler2D textureSampler;

void main()
{
	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColorOut;
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPosOut - vec3(1.0, 1.0, 1.0));
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColorOut;
	vec3 result = (ambient + diffuse) * objectColorOut;

	color = texture(textureSampler, textureCoordinates).rgb * result;
}
