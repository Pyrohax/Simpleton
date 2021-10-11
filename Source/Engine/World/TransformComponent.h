#pragma once

#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>

struct TransformComponent
{
public:
	TransformComponent();
	TransformComponent(const glm::vec3& aPosition);

	void SetPosition(const glm::vec3& aPosition) { myPosition = aPosition; }
	void SetRotation(const glm::vec3& aPosition) { myPosition = aPosition; }
	void SetScale(const glm::vec3& aPosition) { myPosition = aPosition; }

	const glm::vec3& GetPosition() const { return myPosition; }
	const glm::vec3& GetRotation() const { return myRotation; }
	const glm::vec3& GetScale() const { return myScale; }

	float* GetRawPosition() { return glm::value_ptr(myPosition); }

private:
	glm::vec3 myPosition;
	glm::vec3 myRotation;
	glm::vec3 myScale;
};
