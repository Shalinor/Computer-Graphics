#include "Game.h"


Game::Game()
{
}

Game::~Game()
{
	if (solarSystem)
	{
		solarSystem->clear();
		solarSystem = NULL;
		delete solarSystem;
	}
}

int		Game::Startup()
{
	if (glfwInit() == false)
		return -1;

	window = glfwCreateWindow(1280, 720, "Computer Graphics", nullptr, nullptr);

	if (window == nullptr)
	{
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}

	Gizmos::create();

	CreateCamera();

	//Set background colour
	//glClearColor(0.25f, 0.25f, 0.25f, 1.f);
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glEnable(GL_DEPTH_TEST);	//Enables the depth buffer


	SetupSolarSystem();


	//Successfully started up
	return 1;
}

void	Game::Shutdown()
{
	Gizmos::destroy();
	glfwDestroyWindow(window);
	glfwTerminate();
}

bool	Game::Update()
{
	//If game exit triggered, exit
	if ((glfwWindowShouldClose(window) == true) || (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS))
	{
		return false;
	}
	
	//CalculateDelta();
	float	dt = GetDeltaTime();


	//Our game logic and update code goes here!

	if (solarSystem != NULL)
	{
		SolarSystem_Update();
	}

	//Update successful
	return true;
}

void	Game::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//Clear screen
	
	Gizmos::clear();


	//Call desired draw functions/code here
	if (solarSystem != NULL)
	{
		SolarSystem_Draw();
	}

//	DisplayGizmosGrid(21, 10);
//	DisplayGizmosAxis();


	Gizmos::draw(projection * view);

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void	Game::CreateCamera()
{
	view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));						//Eye, Center, Up
	projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);	//Fovy, Aspect, Near, Far
}

void	Game::DisplayGLVersion()
{
	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL: %i.%.\n", major, minor);
}

void	Game::DisplayGizmosAxis(float scale_)
{
	Gizmos::addTransform(glm::mat4(1), scale_);
}

void	Game::DisplayGizmosGrid(int gridSize_, int gridSpacing_)
{
	vec4 white(1.f);
	vec4 black(0.f, 0.f, 0.f, 1.f);

	for (int i = 0; i < gridSize_; ++i)
	{
		Gizmos::addLine(vec3(-gridSpacing_ + i, 0, gridSpacing_), vec3(-gridSpacing_ + i, 0, -gridSpacing_), i == gridSpacing_ ? white : black);
		Gizmos::addLine(vec3(gridSpacing_, 0, -gridSpacing_ + i), vec3(-gridSpacing_, 0, -gridSpacing_ + i), i == gridSpacing_ ? white : black);
	}
}

void	Game::SolarSystem_Update()
{
	if (solarSystem != NULL)
	{
		for (systemIterator = solarSystem->begin(); systemIterator != solarSystem->end(); ++systemIterator)
		{
			(*systemIterator)->CalcPosition();
		}
	}
}

void	Game::SolarSystem_Draw()
{
	if (solarSystem != NULL)
	{
		for (systemIterator = solarSystem->begin(); systemIterator != solarSystem->end(); ++systemIterator)
		{
			(*systemIterator)->Draw(true);
		}
	}
}

void	Game::SetupSolarSystem()
{
	vec4 yellow(1.f, 1.f, 0.1f, 1.f);
	vec4 blue(0.001f, 0.5f, 1.f, 1.f);// (30, 144, 255, 1);
	vec4 grey(0.75f, 0.75f, 0.75f, 1.f);
	vec4 red(1.f, 0.33f, 0.f, 1.f);

	if (solarSystem == NULL)
	{
		solarSystem = new std::vector < Planet* > ;
	}

	//Create and add the Sun
	solarSystem->push_back(new Planet(0.f, 1.25f, 0.f, 50, 50, yellow));	//Create & add Sun


	//Create and add Earth & the moon
	Planet* planet = new Planet(5.f, 0.25f, 0.01f, 10, 10, blue);			//Create Earth
	planet->AddMoon(0.75f, 0.0625f, 0.125f, 10, 10, grey);					//Add Moon to Earth

	solarSystem->push_back(planet);											//Add Earth & Moon


	//Create and add Mars & moons
	planet = new Planet(7.f, 0.25f, 0.02f, 10, 10, red);					//Create Mars
	planet->AddMoon(0.4f, 0.0625f, -0.2f, 10, 10, grey);					//Add Phobos to Mars
	planet->AddMoon(0.9f, 0.0625f, 0.05f, 10, 10, grey);					//Add Deimos to Mars

	solarSystem->push_back(planet);											//Add Earth & Moon
}
