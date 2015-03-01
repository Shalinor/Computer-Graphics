#include "Planet.h"


Planet::Planet()
{
}

Planet::Planet(float distanceFromTheSun_, float radius_, float orbitSpeed_, int rows_, int columns_, vec4 colour_)
{
	distanceFromSun = distanceFromTheSun_;
	radius = radius_;
	orbitSpeed = orbitSpeed_;
	rows = rows_;
	columns = columns_;
	colour = colour_;
	orbitAngle = 0.f;
	rotation = 0.f;
	position = vec3(0.f);
	axis = vec3(0.f, 1.f, 0.f);
}


Planet::~Planet()
{
}

void	Planet::CalcPosition()
{
	if (distanceFromSun > 0.f)
	{
		orbitAngle += orbitSpeed;//365/6.283185f;							//increment per frame

		position.x = (float)(glm::sin((double)orbitAngle) * distanceFromSun);
		position.y = 0.f;
		position.z = (float)(glm::cos((double)orbitAngle) * distanceFromSun);
	}

	rotation += 1.080859f;

	//printf("%f\n", orbitAngle);

	for (moonIterator = moon.begin(); moonIterator != moon.end(); ++moonIterator)
	{
		(*moonIterator)->CalcPosition();
	}
}

void	Planet::Draw(bool displayOrbit_)
{
	for (moonIterator = moon.begin(); moonIterator != moon.end(); ++moonIterator)
	{
		(*moonIterator)->Draw(position, displayOrbit_);
	}

	mat4 transform = glm::rotate(rotation, axis);

	Gizmos::addSphere(position, radius, rows, columns, colour, &transform);

	if (distanceFromSun > 0.f && displayOrbit_)
	{
		//Gizmos::addDisk(vec3(0), 5.f, 50, colour, &transform);
		//Gizmos::addRing(center, innerRadius, outerRadius, segments, colour, &transform);
		Gizmos::addRing(vec3(0), (distanceFromSun - 0.01f), (distanceFromSun + 0.01f), 50, vec4(1.f), &transform);
	}
}

void	Planet::AddMoon(float distanceFromPlanet_, float radius_, float orbitSpeed_, int rows_, int columns_, vec4 colour_)
{
	moon.push_back(std::make_shared<Moon>(distanceFromPlanet_, radius_, orbitSpeed_, rows_, columns_, colour_));
}