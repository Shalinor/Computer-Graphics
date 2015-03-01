#pragma once
#define GLM_FORCE_PURE

#include <aie/Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <vector>
#include <memory>

using	glm::vec3;
using	glm::vec4;
using	glm::mat4;

#include "moon.h"

class Planet
{
public:
			Planet();
			Planet(float distanceFromTheSun_, float radius_, float orbitSpeed_, int rows_, int columns_, vec4 colour_);
			~Planet();

	void	CalcPosition();
	void	Draw(bool displayOrbit_);
	void	AddMoon(float distanceFromPlanet_, float radius_, float orbitSpeed_, int rows_, int columns_, vec4 colour_);

private:
	float	distanceFromSun;	//<-that
	float	radius;				//Globe radius
	float	orbitSpeed;			//Speed (and direction) of orbit
	int		rows, columns;		//Sphere resolution
	vec3	position;			//Center
	vec4	colour;				//Colour of globe

	//These are seperate to allow for future differing rotation speed vs orbit speed...
	float	orbitAngle;			//<-that
	float	rotation;			//Rotation around axis
	vec3	axis;				//Axis for rotation

	std::vector<std::shared_ptr<Moon>>				moon;
	std::vector<std::shared_ptr<Moon>>::iterator	moonIterator;
};

