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

	//Pre-set previous mouse positions
	glfwGetCursorPos(window, &previousMouseXPos, &previousMouseYPos);
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

	//vec3	position(0), center(0);
	double	mouseXPos, mouseYPos;
	//With SetPosition(translates by the passed values)
	//position.x zooms (- moves left, + moves right)
	//position.z zooms (- zooms in, + zooms out)
	//position.y zooms (- moves down, + moves up)

	//With SetLookAt(Position, target, "up"), slides around center unless it is updated too...


	//Forward
	if (glfwGetKey(window, GLFW_KEY_W) == true)
	{
		cameraTranslation -= cameraForward * (speed * deltaTime_);
	}

	//Backward
	if (glfwGetKey(window, GLFW_KEY_S) == true)
	{
		cameraTranslation += cameraForward * (speed * deltaTime_);
	}

	//Left
	if (glfwGetKey(window, GLFW_KEY_A) == true)
	{
		cameraTranslation -= cameraRight * (speed * deltaTime_);
	}

	//Right
	if (glfwGetKey(window, GLFW_KEY_D) == true)
	{
		cameraTranslation += cameraRight * (speed * deltaTime_);
	}


	worldTransform[3] = cameraTranslation;

	//Mouse up/down - pitch camera around it's local X axis, left/right - rotate around global "up" (0,1,0)
	glfwGetCursorPos(window, &mouseXPos, &mouseYPos);

	mat4 rot = glm::rotate(mat4(1), (speed * deltaTime_), up);
	
	if (mouseXPos < previousMouseXPos)
	{
		//Rotate "left" around global "up" axis...
		center = glm::rotate(center, (-10.0f /** deltaTime_*/), up);

	}
	else if (mouseXPos > previousMouseXPos)
	{
		//Rotate "right" around global "up" axis...

	}

	if (mouseYPos < previousMouseYPos)
	{
		//Pitch "up" around local x axis...
	//	center.x += (speed * deltaTime_);

	}
	
	if (mouseYPos > previousMouseYPos)
	{
		//Rotate "down" around local x axis...
	//	center.x += (speed * deltaTime_);
	}
	
	this->UpdateProjectionViewTransform();
	//SetLookAt()
	

	////void	Camera::SetLookAt(vec3 from_, vec3 to_, vec3 up_)

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
	
	//mat4 worldTransform[3] == position
	//SetLookAt(cameraTranslation, center, up);
	//SetPosition(position);
}

void	FlyCamera::SetSpeed(float speed_)
{
	speed = speed_;
}
