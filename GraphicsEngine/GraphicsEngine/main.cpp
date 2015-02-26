#define GLM_FORCE_PURE

#include <loadgen/gl_core_4_4.h>
#include <glfw/glfw3.h>

#include <aie/Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <stdio.h>

using	glm::vec3;
using	glm::vec4;
using	glm::mat4;

void	DisplayGLVersion();
void	DisplayGizmosAxis(float scale_ = 1.0f);
void	DisplayGizmosGrid(int gridSize_, int gridSpacing_);
void	DisplaySolarSystem();

int main()
{
	if (glfwInit() == false)
		return -1;

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Computer Graphics", nullptr, nullptr);

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

	mat4 view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
	mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);


	//The rest of our code goes here!

	glClearColor(0.f, 0.f, 0.f, 1.f);//(0.25f, 0.25f, 0.25f, 1.f);	//Set background colour
	glEnable(GL_DEPTH_TEST);	//Enables the depth buffer

	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		//Our game logic and update code goes here!
		//  So does our render code!

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//Clear screen

		Gizmos::clear();

		//DisplayGizmosAxis();

		//DisplayGizmosGrid(21, 10);

		DisplaySolarSystem();



		Gizmos::draw(projection * view);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	Gizmos::destroy();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void	DisplayGLVersion()
{
	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL: %i.%.\n", major, minor);
}

void	DisplayGizmosAxis(float scale_)
{
	Gizmos::addTransform(glm::mat4(1), scale_);
}

void	DisplayGizmosGrid(int gridSize_, int gridSpacing_)
{
	vec4 white(1.f);
	vec4 black(0.f, 0.f, 0.f, 1.f);

	for (int i = 0; i < gridSize_; ++i)
	{
		Gizmos::addLine(vec3(-gridSpacing_ + i, 0, gridSpacing_), vec3(-gridSpacing_ + i, 0, -gridSpacing_), i == gridSpacing_ ? white : black);
		Gizmos::addLine(vec3(gridSpacing_ + i, 0, -gridSpacing_), vec3(-gridSpacing_ + i, 0, -gridSpacing_), i == gridSpacing_ ? white : black);
	}
}

void	DisplaySolarSystem()	//NOT to scale!!!
{
	vec4 yellow(1.f, 1.f, 0.1f, 1.f);
	vec4 blue(0.001f, 0.5f, 1.f, 1.f);// (30, 144, 255, 1);
	vec4 grey(0.75f, 0.75f, 0.75f, 1.f);

	//Jason's rotation - my comments/observations/interpretations...

	//these 2 vars by me to indicate positioning
	//vec3 pos = vec3(0.f, 0.f, 5.f);
	vec3 axis = vec3(0.f, 1.f, 0.f);

	static float rot = 0.f;					//rotation variable - dodgy but works ;P
	rot += 0.01f;							//increment per frame
	mat4 rotation = glm::rotate(rot, axis);	//rotation around given axis

	//orbit in the initial position given, around the axis given
//	vec3 orbit = glm::rotate(pos, rot, axis);

	vec3 earthPos = vec3(0.f, 0.f, 5.f);// 5.f);
	vec3 earthOrbit = glm::rotate(earthPos, rot, axis);
	//vec3 moonPos = vec3(0.75f, 0.f, 5.f);
	vec3 moonPos = vec3(0.75f, 0.f, 0.f);
	vec3 moonOrbit = glm::rotate(moonPos, rot, axis) * earthOrbit;

	mat4 moon = glm::translate(rotation, earthOrbit);
//	glm::translate()
	//rotation is the transform being passed to the sphere (currently just rotating on own axis)
	//need to move the moon to it's point relative to earth...
	//*** Moons offset should be 0.75f,0,0!!!!!!

	/*
	Jarrods Code
		//center points
		mX = -24 * cos(phi);
		mY = 0;
		mZ = 24 * sin(phi);

		Gizmos::addSphere(vec3(mX, mY, mZ),							//center point
							2, 10, 10,								//radius, rows, columns
							vec4(0, 0.5, 1, 1),						//colour
							&glm::rotate(rotation, vec3(0, 1, 0)),	//transform
							0, 360);								//longMin, longMax

		phi += delta + 0.0002;
		if (phi >= 2 * M_PI)
		{
				phi = 0;
		}
	*/

	/*
	Modified from my Tanks game
	Vector2(
		(cosf(playerAngle) * movement.x),	//x
		(sinf(playerAngle) * movement.y))	//y
	*/


//	void Gizmos::addSphere(const glm::vec3& a_center,
//							float a_radius, int a_rows, int a_columns,
//							const glm::vec4& a_fillColour,
//							const glm::mat4* a_transform /*= nullptr*///,
//							float a_longMin /*= 0.f*/, float a_longMax /*= 360*/,
//							float a_latMin /*= -90*/, float a_latMax /*= 90*/)
	

//	Gizmos::addSphere(vec3(0.f), 1.25f, 50, 50, yellow, &rotation);			//Sun

	static float phi = 0.0f;

	static float mX = 10 * cos(phi);
	static float mY = 0;
	static float mZ = 10 * sin(phi);

	Gizmos::addSphere(vec3(mX, mY, mZ),		//center point
		2, 10, 10,							//radius, rows, columns
		vec4(0, 0.5, 1, 1),					//colour
		&rotation);							//transform

	

	Gizmos::addSphere(earthOrbit, 0.25f, 10, 10, blue, &rotation);			//Earth
	Gizmos::addSphere(earthPos, 0.25f, 10, 10, blue, &rotation);			//Earth
	Gizmos::addSphere(moonPos, 0.0625f, 10, 10, grey, &rotation);			//Earth's Moon

	phi += 0.0002f;
	if (phi >= 2.f * glm::pi<float>())
	{
		phi = 0.f;
	}
}
