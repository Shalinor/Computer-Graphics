#pragma once
#define GLM_FORCE_PURE

#include <aie/Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using	glm::vec3;
using	glm::vec4;
using	glm::mat4;

class Moon
{
public:
			Moon();
			Moon(float distanceFromPlanet_, float radius_, float orbitSpeed_, int rows_, int columns_, vec4 colour_);
			~Moon();

	void	CalcPosition();
	void	Draw(vec3 planetPosition_, bool displayOrbit_);

private:
	float	distanceFromPlanet;	//<-that
	float	radius;				//Globe radius
	float	orbitSpeed;			//Speed (and direction) of orbit
	int		rows, columns;		//Sphere resolution
	vec3	position;			//Center
	vec4	colour;				//Colour of globe

	//These are seperate to allow for future differing rotation speed vs orbit speed...
	float	orbitAngle;			//<-that
	float	rotation;			//Rotation around axis
	vec3	axis;				//Axis for rotation
};

