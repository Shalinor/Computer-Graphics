#include "Moon.h"


Moon::Moon()
{
}

Moon::Moon(float distanceFromPlanet_, float radius_, float orbitSpeed_, int rows_, int columns_, vec4 colour_)
{
	distanceFromPlanet = distanceFromPlanet_;
	radius = radius_;
	orbitSpeed = orbitSpeed_;
	rows = rows_;
	columns = columns_;
	colour = colour_;
	orbitAngle = 0.f;
	rotation = 0.f;
	axis = vec3(0.f, 1.f, 0.f);
}


Moon::~Moon()
{
}

void	Moon::CalcPosition()
{
	orbitAngle += orbitSpeed;							//increment per frame. If == planet's orbit, it won't orbit the planet...

	position.x = (float)(glm::sin((double)orbitAngle) * distanceFromPlanet);
	position.y = 0.f;
	position.z = (float)(glm::cos((double)orbitAngle) * distanceFromPlanet);

	//printf("%f\n", glm::radians(27.60969f));
	//6.283185 == 360deg
	//0.481880 == #radians earth orbits/orbit of the moon
	//~= 0.076694 radians per day???
	// *1.5 = 0.115041
	// == 0.125
	//1.080859

	rotation += 0.01f;
}

void	Moon::Draw(vec3 planetPosition_, bool displayOrbit_)
{
	mat4 transform = glm::rotate(rotation, axis);

	Gizmos::addSphere(position + planetPosition_, radius, rows, columns, colour, &transform);

	if (distanceFromPlanet > 0.f && displayOrbit_)
	{
		//Gizmos::addDisk(vec3(0), 5.f, 50, colour, &transform);
		//Gizmos::addRing(center, innerRadius, outerRadius, segments, colour, &transform);
		Gizmos::addRing(planetPosition_, (distanceFromPlanet - 0.01f), (distanceFromPlanet + 0.01f), 50, vec4(1.f), &transform);
	}
}