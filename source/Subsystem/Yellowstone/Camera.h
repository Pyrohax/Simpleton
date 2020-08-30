#pragma once

#include <glm/mat4x4.hpp>

class Camera
{
public:
	Camera();
	~Camera();

public:
	glm::mat4 myProjection;
	glm::mat4 myView;
};
