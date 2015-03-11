#include "RenderGeometry.h"

RenderGeometry::RenderGeometry(std::shared_ptr<FlyCamera>	camera_)
{
	camera = camera_;
}

RenderGeometry::~RenderGeometry()
{
}

int		RenderGeometry::Startup()
{
	CreateShaders();
	GenerateGrid(20, 20);

	//Successfully started up
	return 1;
}

void	RenderGeometry::Shutdown()
{

}

bool	RenderGeometry::Update(float deltaTime_)
{
	return true;
}

void	RenderGeometry::Draw()
{
	Gizmos::addSphere(vec3(0), 5.f, 10.f, 10.f, vec4(1));
	//Jason King : view = glm::lookAt(vec3(100.0f, 100.0f, 100.0f), vec3(0.0f), vec3(0.0f, 1.0f, 0.0f));

	//Jason King : projection = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.f);
	mat4 view = glm::lookAt(vec3(100.0f, 100.0f, 100.0f), vec3(0.0f), vec3(0.0f, 1.0f, 0.0f));
	mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.f);
//	mat4 temp = camera->GetProjection();
	glUseProgram(programID);
	unsigned int projectionViewUniform = glGetUniformLocation(programID, "ProjectionView");
	glUniformMatrix4fv(projectionViewUniform, 1, false, glm::value_ptr(projection * view));//projectionMatrix));	//projection = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.f);

	glBindVertexArray(VAO);
	//unsigned int indexCount = (rows - 1) * (cols - 1) * 6;
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	//Renders in wireframe...
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


void	RenderGeometry::GenerateGrid(unsigned int rows_, unsigned int cols_)
{
	rows = rows_;
	cols = cols_;
	indexCount = (rows - 1) * (cols - 1) * 6;

	Vertex* vertices = new Vertex[rows * cols];

	for (unsigned int r = 0; r < rows; ++r)
	{
		for (unsigned int c = 0; c < cols; ++c)
		{
			vertices[r * cols + c].position = vec4((float)c, 0, (float)r, 1);

			//Create some arbitrary colour based off something that might not be related to tiling a texture
			vec3 colour = vec3(sinf((c / (float)(cols - 1)) * (r / (float)(rows - 1))));
			vertices[r * cols + c].colour = vec4(colour, 1);
		}
	}

	//Defining index count based off quad count (2 triangles per quad)
	unsigned int* indices = new unsigned int[indexCount];

	unsigned int index = 0;
	for (unsigned int r = 0; r < (rows - 1); ++r)
	{
		for (unsigned int c = 0; c < (cols - 1); ++c)
		{
			//Triangle 1
			indices[index++] = r * cols + c;
			indices[index++] = (r + 1) * cols + c;
			indices[index++] = (r + 1) * cols + (c + 1);

			//Triangle 2
			indices[index++] = r * cols + c;
			indices[index++] = (r + 1) * cols + (c + 1);
			indices[index++] = r * cols + (c + 1);
		}
	}

	//Generate our GL Buffers
	//Lets move these so that they are all generated together
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	//Add the following line to generate a VertexArrayObject
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	//Create and bind buffers to a vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, (rows * cols) * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)));
	

	//IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);




	glBindVertexArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	delete[] indices;
	delete[] vertices;
}

void	RenderGeometry::CreateShaders()
{
	//Create shaders

	const char* vertexShaderCode = "#version 410\n \
								   		layout(location=0) in vec4 Position; \
										layout(location=1) in vec4 Colour; \
										out vec4 vColour; \
										uniform mat4 ProjectionView; \
										void main() { vColour = Colour; gl_Position = ProjectionView * Position; }";

	//Need to add the two new uniforms into code as per the existing ProjectionView uniform
	/*const char* vertexShaderCode = "#version 410\n \
										layout(location=0) in vec4 Position; \
										layout(location=1) in vec4 Colour; \
										out vec4 vColour; \
										uniform mat4 ProjectionView; \
										uniform float time; \
										uniform float heightScale; \
										void main() { vColour = Colour; vec4 P = Position; P.y += sin( time + Position.x ) * heightScale; gl_Position = ProjectionView * P; }";*/
	

	const char* fragmentShaderCode = "#version 410\n \
									 	in vec4 vColour; \
										out vec4 FragColor; \
										void main() { FragColor = vColour; }";

	int success = GL_FALSE;
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, (const char**)&vertexShaderCode, 0);
	glCompileShader(vertexShader);
	glShaderSource(fragmentShader, 1, (const char**)&fragmentShaderCode, 0);
	glCompileShader(fragmentShader);

	programID = glCreateProgram();
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		int infoLogLength = 0;
		//glGetShaderiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);

		char* infoLog = new char[infoLogLength + 1];//];

		//glGetShaderInfoLog(programID, infoLogLength, 0, infoLog);
		glGetProgramInfoLog(programID, infoLogLength, 0, infoLog);
		printf("Error: Failed to link shader program!\n");
		printf("%s\n", infoLog);
		delete[] infoLog;
	}

	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	projectionViewUniform = glGetUniformLocation(programID, "ProjectionView");
}

