#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Camera
{
public:
	Camera();
	~Camera();

	void Update();

public:
	glm::mat4 myProjection;
	glm::mat4 myView;
	glm::vec3 myPosition;
	glm::vec3 myFront;
	glm::vec3 myRight;
	glm::vec3 myUp;
};
