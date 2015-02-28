#include "Application.h"


Application::Application()
{
	fpsSecondCount = 0.0f;
	fpsFrameCount = 0;
	fps = 0;
	deltaTime = 0.0f;
	prevTime = std::chrono::high_resolution_clock::now();
	coutFPS = false;
}

Application::~Application()
{
}

//Delta/FPS Functions
//void Application::CalculateDelta()
//{
//	currentTime = std::chrono::high_resolution_clock::now();
//
//	//Delta Time
//	deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - prevTime).count();
//
//	prevTime = currentTime;
//}

void Application::CalculateFPS()
{
	fpsSecondCount += GetDeltaTime();
	++fpsFrameCount;

	if (fpsSecondCount >= 1.0f)
	{
		fps = fpsFrameCount;

		//Reset for next second
		fpsSecondCount -= 1.0f;
		fpsFrameCount = 0;
	}

	if (coutFPS)
	{
		std::cout << fps << std::endl;
	}
}

float Application::GetDeltaTime()
{
	currentTime = std::chrono::high_resolution_clock::now();

	//Delta Time
	deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - prevTime).count();

	prevTime = currentTime;
	
	return deltaTime;
}