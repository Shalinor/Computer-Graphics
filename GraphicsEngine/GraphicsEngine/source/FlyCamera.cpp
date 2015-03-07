#include "FlyCamera.h"

FlyCamera::FlyCamera(GLFWwindow* window_)
{
	Camera();
	window = window_;
	up = vec3(0, 1, 0);
	center = vec3(0);
	position = vec3(10, 10, 10);

	//Lock mouse to the window and hide it - also re-centers it
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

FlyCamera::~FlyCamera()
{
}

void	FlyCamera::Update(float deltaTime_)
{
	glm::vec4 cameraRight = this->GetWorldTransform()[0];
	glm::vec4 cameraUp = this->GetWorldTransform()[1];
	glm::vec4 cameraForward = this->GetWorldTransform()[2];
	glm::vec4 cameraTranslation = this->GetWorldTransform()[3];

	double	mouseXPos, mouseYPos;
	//With SetPosition(translates by the passed values)
	//position.x zooms (- moves left, + moves right)
	//position.z zooms (- zooms in, + zooms out)
	//position.y zooms (- moves down, + moves up)

	//With SetLookAt(Position, target, "up"), slides around center unless it is updated too...


	//Reset view to 0
	if (glfwGetKey(window, GLFW_KEY_C) == (int)true)
	{
		SetLookAt(vec3(cameraTranslation), vec3(0), up);
	}

	//Forward
	if (glfwGetKey(window, GLFW_KEY_W) == (int)true)
	{
		cameraTranslation -= cameraForward * (movementSpeed * deltaTime_);
	}

	//Backward
	if (glfwGetKey(window, GLFW_KEY_S) == (int)true)
	{
		cameraTranslation += cameraForward * (movementSpeed * deltaTime_);
	}

	//Left
	if (glfwGetKey(window, GLFW_KEY_A) == (int)true)
	{
		cameraTranslation -= cameraRight * (movementSpeed * deltaTime_);
	}

	//Right
	if (glfwGetKey(window, GLFW_KEY_D) == (int)true)
	{
		cameraTranslation += cameraRight * (movementSpeed * deltaTime_);
	}

	//Up
	if (glfwGetKey(window, GLFW_KEY_SPACE) == (int)true)
	{
		cameraTranslation += cameraUp * (movementSpeed * deltaTime_);
	}

	//Down
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == (int)true)
	{
		cameraTranslation -= cameraUp * (movementSpeed * deltaTime_);
	}

	////Rolls work but the lateral movements are screwed up by the roll... can't be fussed to work on it at present :/
	////Roll Left
	//if (glfwGetKey(window, GLFW_KEY_Q) == (int)true)
	//{
	//	mat4 rot = glm::rotate(mat4(1), (1.5f * rotationSpeed * deltaTime_), vec3(cameraForward));
	//	worldTransform[0] = glm::normalize(rot * cameraRight);
	//	worldTransform[1] = glm::normalize(rot * cameraUp);
	//	worldTransform[2] = glm::normalize(rot * cameraForward);
	//}

	////Roll Right
	//if (glfwGetKey(window, GLFW_KEY_E) == (int)true)
	//{
	//	mat4 rot = glm::rotate(mat4(1), -(1.5f * rotationSpeed * deltaTime_), vec3(cameraForward));
	//	worldTransform[0] = glm::normalize(rot * cameraRight);
	//	worldTransform[1] = glm::normalize(rot * cameraUp);
	//	worldTransform[2] = glm::normalize(rot * cameraForward);
	//}


	worldTransform[3] = cameraTranslation;


	//This is VERY Jerky :/
	//Mouse up/down - pitch camera around it's local X axis, left/right - rotate around global "up" (0,1,0)
	glfwGetCursorPos(window, &mouseXPos, &mouseYPos);

	float movementX = (float)mouseXPos - previousMouseXPos;
	float movementY = (float)mouseYPos - previousMouseYPos;
	previousMouseXPos = (float)mouseXPos;
	previousMouseYPos = (float)mouseYPos;
	
	if (movementX != 0)
	{
		mat4 rot = glm::rotate(mat4(1), (-movementX * rotationSpeed * deltaTime_), up);
		worldTransform[0] = (rot * cameraRight);
		worldTransform[1] = (rot * cameraUp);
		worldTransform[2] = (rot * cameraForward);
	}

	if (movementY != 0)
	{
		mat4 rot = glm::rotate(mat4(1), (-movementY * rotationSpeed * deltaTime_), vec3(cameraRight));
		worldTransform[0] = glm::normalize(rot * cameraRight);
		worldTransform[1] = glm::normalize(rot * cameraUp);
		worldTransform[2] = glm::normalize(rot * cameraForward);
	}
	
/*
	//Scroll input
	//If you wish to be notified when the user scrolls, whether with a mouse wheel or touchpad gesture, set a scroll callback.

	glfwSetScrollCallback(window, scroll_callback);

	//The callback function receives two-dimensional scroll offsets.

	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
	}

	//A simple mouse wheel, being vertical, provides offsets along the Y-axis.
*/

	this->UpdateProjectionViewTransform();
}

void	FlyCamera::SetMovementSpeed(float movementSpeed_)
{
	movementSpeed = movementSpeed_;
}

void	FlyCamera::SetRotationSpeed(float rotationSpeed_)
{
	rotationSpeed = rotationSpeed_;
}
