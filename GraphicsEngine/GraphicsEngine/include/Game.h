#pragma once
#define GLM_FORCE_PURE

#include <memory>
#include <vector>

#include "Application.h"
#include "GameType.h"

#include "SolarSystem.h"

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

private:
	void	CreateCamera();

	GLFWwindow*					window;
	mat4						view;
	mat4						projection;

	std::shared_ptr<GameType>	gameType;
};
