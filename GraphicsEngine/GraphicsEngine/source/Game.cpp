#include "Game.h"


Game::Game()
{
	//Set the desired gameType
	gameType = std::make_shared<SolarSystem>();
}

Game::~Game()
{
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

	camera = std::make_shared<FlyCamera>(window);

	SetupCamera();

	//Set background colour
	glClearColor(0.25f, 0.25f, 0.25f, 1.f);
	//glClearColor(0.f, 0.f, 0.f, 1.f);
	glEnable(GL_DEPTH_TEST);	//Enables the depth buffer


	//Successfully started up
	//return 1;
	return gameType->Startup();	//Return the result of the game's Startup
}

void	Game::Shutdown()
{
	gameType->Shutdown();		//Call the game's Shutdown

	Gizmos::destroy();
	glfwDestroyWindow(window);
	glfwTerminate();
}

bool	Game::Update()
{
	//If game exit triggered, exit
	if ((glfwWindowShouldClose(window) == (int)true) || (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS))
	{
		return false;
	}
	
	//CalculateDelta();
	float	dt = GetDeltaTime();

	camera->Update(dt);

	//Our game logic and update code goes here!

	return gameType->Update(dt);	//Return the result of the game's Update

	//Update successful
	//return true;
}

void	Game::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//Clear screen
	
	Gizmos::clear();


	//Call desired draw functions/code here
	DisplayGizmosGrid(21, 10);
//	DisplayGizmosAxis();

	gameType->Draw();		//Call the game's Draw


	Gizmos::draw(camera->GetProjectionView());

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void	Game::SetupCamera()
{
	camera->SetPerspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 500.f);
	camera->SetLookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
	camera->SetMovementSpeed(5.f);
	camera->SetRotationSpeed(1.f);

	//view = glm::lookAt(vec3(5, 5, 5), vec3(0), vec3(0, 1, 0));						//Eye, Center, Up
	//projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 500.f);	//Fovy, Aspect, Near, Far
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
