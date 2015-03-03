#pragma once
#define GLM_FORCE_PURE

#include <glfw/glfw3.h>

#include <aie/Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "Camera.h"

using glm::vec3;
using glm::mat4;

class FlyCamera : public Camera
{
public:
			FlyCamera(GLFWwindow* window_);
			~FlyCamera();

	void	Update(float deltaTime_);
	void	SetSpeed(float speed_);

private:
	GLFWwindow*	window;
	float		speed;
	vec3		up;
	vec3		direction;
	vec3		center;

	double		previousMouseXPos, previousMouseYPos;
};

