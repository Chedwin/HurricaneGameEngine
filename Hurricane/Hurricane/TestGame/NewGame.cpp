//#include <ShaderProgramManager.h>
#include <FlyCamera.h>
#include <ImageManager.h>
#include "NewGame.h"

NewGame::NewGame()
{
	_gameInstance = this;
	//fpsCam = nullptr;
}

NewGame::~NewGame()
{
	//delete box;
	//delete box2;
	cubeShader->UnuseShader();

	glDeleteBuffers(2, buffers);
}


/////////////////////////////////////////////////////////////////////////////////////////

//GLuint triangleVerts[] = {
//	-0.5f, -0.5f, 0.0f,
//	 0.0f,  0.3f, 0.0f,
//	 0.5f, -0.5f, 0.0f,
//};
GLuint TextureID = 0;
/////////////////////////////////////////////////////////////////////////////////////////
enum VAO_IDs { Triangles, NumVAOs };
GLuint VAOs[NumVAOs];
GLuint texture[1];
const GLuint NumVertices = 4;
GLenum data_fmt;
float time = 0;
hBOOL NewGame::InitGame()
{
	// CREATE THE SHADERS
	cubeShader = new ShaderProgram("My Cube Shader");
	cubeShader->CompileShaders("../shaders/colourShading.vert", "../shaders/colourShading.frag");
	cubeShader->AddAttribute("vertexPosition");
	cubeShader->AddAttribute("vertexColor");
	cubeShader->AddAttribute("vertexUV");
	cubeShader->LinkShaders();

	// Store shader in manager
	SHADER_MANAGER->StoreShaderProg(cubeShader->GetProgramName(), cubeShader);

	
	appleImage = new SdlImage("apple.png", "ApplePicture");


	IMAGE_MANAGER->UploadImage(appleImage->GetName(), appleImage);

	// USE THE SHADER PROGRAM
	cubeShader->UseShader();

	// Creatint texture
	GLfloat textureCoordinates[4][2] = {
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f
	};

	GLint _width_ = appleImage->GetWidth();
	GLuint _height_ = appleImage->GetHeight();
	void* image = appleImage->GetImageSurface()->pixels;
	

	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, appleImage->GetWidth(), appleImage->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, appleImage->GetImageSurface()->pixels);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);


	GLfloat vertices[NumVertices][2]= {
		{ -0.90f, -0.90f }, // Square
		{ 0.9f, -0.9f },
		{ 0.90f, 0.9f },
		{ -0.9f, 0.9f }
	};


	GLfloat colorData[NumVertices][3] = {
		{ 1,1,0 }, // color for vertices
		{ 1,1,0 },
		{ 1,0,1 },
		{ 1,1,1 }
	};


	glGenBuffers(3, buffers);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoordinates), textureCoordinates, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);



	// Set location of uniform variables of matrices in shader
	location = cubeShader->GetUniformLocation("model_matrix");
	view_matrix_location = cubeShader->GetUniformLocation("view_matrix");
	projection_matrix_location = cubeShader->GetUniformLocation("projection_matrix");


	FLY_DEBUG_CAM->SetProjLocation(projection_matrix_location);
	FLY_DEBUG_CAM->SetViewLocation(view_matrix_location);
	FLY_DEBUG_CAM->SetPostion(VEC3(0.0f, 0.0f, 1.0f));
	//box = new Box();
	//box2 = new Box();
	return true;
}

void NewGame::GameUpdate(const hFLOAT _deltaTime)
{
	// window title bar update
	STRINGSTREAM ss;
	ss << "New Game! | FPS: " << fps;
	STRING _fps = ss.str();

	SDL_SetWindowTitle(gameWindow->GetWindow(), _fps.c_str());
	time += 0.001f;
	//fpsCam->Update(_deltaTime);
	FLY_DEBUG_CAM->Update(_deltaTime);
}

void NewGame::GameRender()
{
	//// Draw the triangle !
	glm::mat4 model_view = glm::mat4(1.0f);
	glUniformMatrix4fv(location, 1, GL_FALSE, &model_view[0][0]);
	//box->Render();

	GLint textureLocation = cubeShader->GetUniformLocation("mySampler");

	glUniform1i(textureLocation, 0);

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glDrawArrays(GL_QUADS, 0, NumVertices);
}

void NewGame::GameInput(SDL_Event & _evnt)
{
	FLY_DEBUG_CAM->MoveCamera(_evnt);
}
