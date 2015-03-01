#pragma once

#include "GameType.h"

#include "Moon.h"
#include "Planet.h"

#include <vector>

class SolarSystem : public GameType
{
	int		Startup();
	void	Shutdown();

	bool	Update(float deltaTime_);
	void	Draw();

private:
	std::vector<std::shared_ptr<Planet>>			solarSystem;
	std::vector<std::shared_ptr<Planet>>::iterator	systemIterator;
};