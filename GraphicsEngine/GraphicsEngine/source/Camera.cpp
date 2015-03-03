#include "Camera.h"

Camera::Camera()
{
	worldTransform = mat4();
}

Camera::~Camera()
{
}

void	Camera::Update(float deltaTime_)
{
}

void	Camera::SetPerspective(float fieldOfView_, float aspectRatio_, float near_, float far_)
{
	projectionTransform = glm::perspective(fieldOfView_, aspectRatio_, near_, far_);
}

void	Camera::SetLookAt(vec3 from_, vec3 to_, vec3 up_)
{
	viewTransform = glm::lookAt(from_, to_, up_);
	worldTransform = glm::inverse(viewTransform);

	UpdateProjectionViewTransform();
}

void	Camera::SetPosition(vec3 position_)
{
	worldTransform = glm::translate(worldTransform, position_);
	viewTransform = glm::inverse(worldTransform);

	UpdateProjectionViewTransform();
}

mat4	Camera::GetWorldTransform()
{
	return worldTransform;
}

mat4	Camera::GetView()
{
	return viewTransform;
}

mat4	Camera::GetProjection()
{
	return projectionTransform;
}

mat4	Camera::GetProjectionView()
{
	return projectionViewTransform;
}

void	Camera::UpdateProjectionViewTransform()
{
	projectionViewTransform = projectionTransform * viewTransform;
}
