#pragma once
#define GLM_FORCE_PURE

#include <aie/Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::mat4;

class Camera
{
public:
					Camera();
					~Camera();

					virtual void	Update(float deltaTime_);// = 0;

	void			SetPerspective(float fieldOfView_, float aspectRatio_, float near_, float far_);	//Defines your view
	void			SetLookAt(vec3 from_, vec3 to_, vec3 up_);											//Sets the Camera position and orientation
	void			SetPosition(vec3 position_);														//Sets the Camera position without effecting orientation
	mat4			GetWorldTransform();																//Returns worldTransform
	mat4			GetView();																			//Returns viewTransform
	mat4			GetProjection();																	//Returns projectionTransform
	mat4			GetProjectionView();																//Returns projectionViewTransform - used by Gizmos to draw

protected:
	//Call this if the worldTransform ever changes
	void			UpdateProjectionViewTransform();													//Updates the projectionViewTransform

	mat4			worldTransform;				//<- That
	mat4			viewTransform;				//<- That
	mat4			projectionTransform;		//<- That	(AKA projectionMatrix)
	mat4			projectionViewTransform;	//<- That
};