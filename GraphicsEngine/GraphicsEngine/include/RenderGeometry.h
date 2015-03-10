#pragma once
#define GLM_FORCE_PURE

#include <loadgen/gl_core_4_4.h>
#include <glfw/glfw3.h>

#include <aie/Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

//#include <iostream>
//#include <chrono>
//#include <stdio.h>

#include "Camera.h"
#include "FlyCamera.h"

#include <memory>

using	glm::vec3;
using	glm::vec4;
using	glm::mat4;

struct Vertex
{
	vec4	position;
	vec4	colour;
};

#include "GameType.h"

class RenderGeometry : public GameType
{
public:
	RenderGeometry(std::shared_ptr<FlyCamera>	camera_);
	~RenderGeometry();

	int				Startup();
	void			Shutdown();

	bool			Update(float deltaTime_);
	void			Draw();

	void			GenerateGrid(unsigned int rows_, unsigned int cols_);

private:
	std::shared_ptr<FlyCamera>	camera;

	unsigned int	rows;
	unsigned int	cols;

	//Vertex and index buffers
	unsigned int	VAO;
	unsigned int	VBO;
	unsigned int	IBO;

	unsigned int	programID;	//Shader
	unsigned int	indexCount;
	unsigned int	projectionViewUniform;

	void			CreateShaders();
};