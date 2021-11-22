#pragma once

#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>

struct LightingComponent
{
public:
	LightingComponent();
	LightingComponent(const glm::vec3& aColor);

	void SetColor(const float aX, const float aY, const float aZ) { myColor = glm::vec3(aX, aY, aZ); }
	void SetColor(const glm::vec3& aColor) { myColor = aColor; }

	const glm::vec3& GetColor() const { return myColor; }
	float* GetRawColor() { return glm::value_ptr(myColor); }

private:
	glm::vec3 myColor;
};
