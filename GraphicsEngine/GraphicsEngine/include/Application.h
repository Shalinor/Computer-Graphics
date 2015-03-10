#pragma once
#define GLM_FORCE_PURE

#include <loadgen/gl_core_4_4.h>
#include <glfw/glfw3.h>

#include <aie/Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <iostream>
#include <chrono>
#include <stdio.h>

#include "Camera.h"
#include "FlyCamera.h"

using	glm::vec3;
using	glm::vec4;
using	glm::mat4;

class Application
{
public:
	Application();
	~Application();

	virtual int Startup() = 0;
	virtual void Shutdown() = 0;

	virtual bool Update() = 0;
	virtual void Draw() = 0;

	float	GetDeltaTime();
//	void	CalculateDelta();
	void	CalculateFPS();

private:
	float	deltaTime;
	float	fpsSecondCount;
	int		fpsFrameCount;
	int		fps;
	bool	coutFPS;

	std::chrono::time_point<std::chrono::high_resolution_clock> currentTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> prevTime;
};

