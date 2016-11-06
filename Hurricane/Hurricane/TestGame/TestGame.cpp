#include <ShaderProgramManager.h>
#include "TestGame.h"

TestGame::TestGame()
{
	_gameInstance = this;
}

TestGame::~TestGame()
{
	cubeShader->UnuseShader();
	glDeleteBuffers(2, buffers);
	glDeleteVertexArrays(1, &VertexArrayID);
}


/////////////////////////////////////////////////////////////////////////////////////////

static const GLfloat g_vertex_buffer_data[] = {
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f
};

// One color for each vertex. They were generated randomly.
static const GLfloat g_color_buffer_data[] = {
	0.583f,  0.771f,  0.014f,
	0.609f,  0.115f,  0.436f,
	0.327f,  0.483f,  0.844f,
	0.822f,  0.569f,  0.201f,
	0.435f,  0.602f,  0.223f,
	0.310f,  0.747f,  0.185f,
	0.597f,  0.770f,  0.761f,
	0.559f,  0.436f,  0.730f,
	0.359f,  0.583f,  0.152f,
	0.483f,  0.596f,  0.789f,
	0.559f,  0.861f,  0.639f,
	0.195f,  0.548f,  0.859f,
	0.014f,  0.184f,  0.576f,
	0.771f,  0.328f,  0.970f,
	0.406f,  0.615f,  0.116f,
	0.676f,  0.977f,  0.133f,
	0.971f,  0.572f,  0.833f,
	0.140f,  0.616f,  0.489f,
	0.997f,  0.513f,  0.064f,
	0.945f,  0.719f,  0.592f,
	0.543f,  0.021f,  0.978f,
	0.279f,  0.317f,  0.505f,
	0.167f,  0.620f,  0.077f,
	0.347f,  0.857f,  0.137f,
	0.055f,  0.953f,  0.042f,
	0.714f,  0.505f,  0.345f,
	0.783f,  0.290f,  0.734f,
	0.722f,  0.645f,  0.174f,
	0.302f,  0.455f,  0.848f,
	0.225f,  0.587f,  0.040f,
	0.517f,  0.713f,  0.338f,
	0.053f,  0.959f,  0.120f,
	0.393f,  0.621f,  0.362f,
	0.673f,  0.211f,  0.457f,
	0.820f,  0.883f,  0.371f,
	0.982f,  0.099f,  0.879f
};

/////////////////////////////////////////////////////////////////////////////////////////

hBOOL TestGame::InitGame()
{
	// CREATE THE SHADERS
	cubeShader = new ShaderProgram();
	cubeShader->CompileShaders("colourShading.vert", "colourShading.frag");
	cubeShader->LinkShaders();

	// Store shader in manager
	STRING name = "My Cube Shader";
	SHADER_MANAGER->StoreShaderProg(name, cubeShader);

	cubeShader->UseShader();

	// Create Vertex Array
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// GEN buffers
	glGenBuffers(2, buffers);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glBindAttribLocation(cubeShader->GetProgramID(), 0, "vertexPosition");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
	glBindAttribLocation(cubeShader->GetProgramID(), 1, "vertexColor");
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	// Set location of uniform variables of matrices in shader
	location = glGetUniformLocation(cubeShader->GetProgramID(), "model_matrix");
	view_matrix_location = glGetUniformLocation(cubeShader->GetProgramID(), "view_matrix");
	projection_matrix_location = glGetUniformLocation(cubeShader->GetProgramID(), "projection_matrix");

	return true;
}

void TestGame::GameUpdate(const hFLOAT _deltaTime)
{
	// window title bar update
	STRINGSTREAM ss;
	ss << "Test Cube | FPS: " << fps;
	STRING _fps = ss.str();

	SDL_SetWindowTitle(gameWindow->GetWindow(), _fps.c_str());
}

void TestGame::GameRender()
{
	// Draw the triangle !
	glm::mat4 Model = glm::mat4(1.0f);
	glUniformMatrix4fv(location, 1, GL_FALSE, &Model[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12*3 indices starting at 0 -> 12 triangles

	// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(4, 3, -3), // Camera is at (4,3,-3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
	glUniformMatrix4fv(view_matrix_location, 1, GL_FALSE, &View[0][0]);

	// Model matrix : an identity matrix (model will be at the origin)

	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	glUniformMatrix4fv(projection_matrix_location, 1, GL_FALSE, &Projection[0][0]);
}

void TestGame::GameInput(SDL_Event & _evnt)
{
}
