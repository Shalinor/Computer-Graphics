#include "Game.h"

int	SolarSystem::Startup()
{
	/*
	std::vector<std::shared_ptr<Planet>>			solarSystem;
	std::vector<std::shared_ptr<Planet>>::iterator	systemIterator;
	*/

	vec4 yellow(1.f, 1.f, 0.1f, 1.f);
	vec4 blue(0.001f, 0.5f, 1.f, 1.f);
	vec4 grey(0.75f, 0.75f, 0.75f, 1.f);
	vec4 red(1.f, 0.33f, 0.f, 1.f);

	//Create and add the Sun
	solarSystem.push_back(std::make_shared<Planet>(0.f, 1.25f, 0.f, 50, 50, yellow));			//Create & add Sun


	//Create and add Earth & the moon
	std::shared_ptr<Planet> planet = std::make_shared<Planet>(5.f, 0.25f, 0.01f, 10, 10, blue);	//Create Earth
	planet->AddMoon(0.75f, 0.0625f, 0.125f, 10, 10, grey);										//Add Moon to Earth

	solarSystem.push_back(planet);																//Add Earth & Moon


	//Create and add Mars & moons
	planet = std::make_shared<Planet>(7.f, 0.25f, 0.02f, 10, 10, red);							//Create Mars
	planet->AddMoon(0.4f, 0.0625f, -0.2f, 10, 10, grey);										//Add Phobos to Mars
	planet->AddMoon(0.9f, 0.0625f, 0.05f, 10, 10, grey);										//Add Deimos to Mars

	solarSystem.push_back(planet);																//Add Earth & Moon

	return 1;
}


void	SolarSystem::Shutdown()
{
}

void	SolarSystem::Draw()
{
	for (systemIterator = solarSystem.begin(); systemIterator != solarSystem.end(); ++systemIterator)
	{
		(*systemIterator)->Draw(true);
	}
}

bool	SolarSystem::Update(float deltaTime_)
{
	for (systemIterator = solarSystem.begin(); systemIterator != solarSystem.end(); ++systemIterator)
	{
		(*systemIterator)->CalcPosition();
	}

	//Update successful
	return true;
}