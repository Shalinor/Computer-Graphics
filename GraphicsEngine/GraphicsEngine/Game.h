#pragma once
#define GLM_FORCE_PURE

#include <vector>

#include "Application.h"

#include "Moon.h"
#include "Planet.h"

class Game :
	public Application
{
public:
			Game();
			~Game();

	 int	Startup();
	 void	Shutdown();

	 bool	Update();
	 void	Draw();

	 void	DisplayGLVersion();

	 void	DisplayGizmosAxis(float scale_ = 1.0f);
	 void	DisplayGizmosGrid(int gridSize_, int gridSpacing_);

	 void	SetupSolarSystem();

private:
	void	CreateCamera();
	void	SolarSystem_Update();
	void	SolarSystem_Draw();


	GLFWwindow*	window;
	mat4		view;
	mat4		projection;

	std::vector<Planet*>			*solarSystem;
	std::vector<Planet*>::iterator	systemIterator;
};

