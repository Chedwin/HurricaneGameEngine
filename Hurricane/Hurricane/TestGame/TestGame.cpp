#include "TestGame.h"
#include <SdlImage.h>


TestGame::TestGame() : _shaderManager(nullptr), _imageManager(nullptr)
{
	_gameInstance = this;
}

TestGame::~TestGame() 
{
	delete cam3D;
	cam3D = nullptr;

	_shaderProgram->UnuseShader();

	glDeleteBuffers(2, Buffers);

	_shaderManager = nullptr;
	_imageManager = nullptr;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
hBOOL TestGame::InitGame() 
{
	cam3D = new Camera(levelToLoad);
	cam3D->Init(properties->GetVideoProperties()->screenWidth, properties->GetVideoProperties()->screenHeight);

	_shaderManager = SHADER_MANAGER;

	// CREATE THE SHADERS
	_shaderProgram = new ShaderProgram();
	_shaderProgram->CompileShaders("colourShading.vert", "colourShading.frag");
	_shaderProgram->AddAttribute("vertexPosition");
	_shaderProgram->AddAttribute("vertexColor");
	_shaderProgram->LinkShaders();

	STRING name = "myShaderProgram";
	_shaderManager->StoreShaderProg(name, _shaderProgram);

	Vertex v[4];
	v[0].pos = { 0.5f, 0.5f, 0.0f };
	v[1].pos = { 0.5f, -0.5f, 0.0f };
	v[2].pos = { -0.5f, -0.5f, 0.0f };
	v[3].pos = { -0.5f, 0.5f, 0.0f };


	v[0].col = { 255, 0, 0, 1 };
	v[1].col = { 0, 255, 255, 1 };
	v[2].col = { 255, 255, 0, 1 };
	v[3].col = { 0, 0, 255, 1 };



	_shaderProgram->UseShader();


	glGenBuffers(2, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, col));
	glEnableVertexAttribArray(1);


	_shaderLocation = _shaderProgram->GetUniformLocation("model_matrix");
	_viewMatLocation = _shaderProgram->GetUniformLocation("view_matrix");
	_projMatLocation = _shaderProgram->GetUniformLocation("projection_matrix");

	// Image Manager Initialization
	_imageManager = IMAGE_MANAGER;
	_imageManager->UploadFile("res/hurricane.jpg", "HurricaneSplash");
	
	return true;
}

void TestGame::GameRender()
{
	VEC3 loc = VEC3(0.0f, 0.0f, 0.5f);
	VEC3 dir = VEC3(0.0f, 0.0f, -1.0f);
	VEC3 up = VEC3(0.0f, 1.0f, 0.0f);

	MATRIX4 cam_mat = glm::lookAt(loc, dir, up);
	glUniformMatrix4fv(_viewMatLocation, 1, GL_FALSE, &cam_mat[0][0]);

	MATRIX4 proj_matrix = glm::perspective(60.0f, (float)properties->GetVideoProperties()->screenWidth / (float)properties->GetVideoProperties()->screenHeight, 0.1f, 10.0f);
	glUniformMatrix4fv(_projMatLocation, 1, GL_FALSE, &proj_matrix[0][0]);

	MATRIX4 model_view;
	glUniformMatrix4fv(_shaderLocation, 1, GL_FALSE, &model_view[0][0]);
	glDrawArrays(GL_QUADS, 0, 4);
}

void TestGame::GameUpdate(const hFLOAT _deltatime)
{
	STRINGSTREAM ss;
	ss << "Pong | FPS: " << fps;
	STRING _fps = ss.str();

	SDL_SetWindowTitle(renderer->GetWindow(), _fps.c_str());

	cam3D->Update(_deltatime);
}
