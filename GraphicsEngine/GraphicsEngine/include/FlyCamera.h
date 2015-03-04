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
	void	SetMovementSpeed(float movementSpeed_);
	void	SetRotationSpeed(float rotationSpeed_);

private:
	GLFWwindow*	window;
	float		movementSpeed, rotationSpeed, previousMouseXPos, previousMouseYPos;
	vec3		up;
	vec3		position;
	vec3		center;
};
