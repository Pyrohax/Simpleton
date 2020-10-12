#pragma once

#include <glm/vec3.hpp>

class Light
{
public:
	Light();
	~Light();

	void SetColor(const glm::vec3& aColor) { myColor = aColor; }
	void SetPosition(const glm::vec3& aPosition) { myPosition = aPosition; }

	const glm::vec3& GetPosition() const { return myPosition; }
	const glm::vec3& GetColor() const { return myColor; }

private:
	glm::vec3 myPosition;
	glm::vec3 myColor;
};

Light::Light()
	: myPosition(0.0f)
	, myColor(0.0f)
{
}

Light::~Light()
{
}
