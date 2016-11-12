//#include <ShaderProgramManager.h>
#include <FlyCamera.h>
#include <ImageManager.h>
#include "TestGame.h"

TestGame::TestGame()
{
	_gameInstance = this;
	//fpsCam = nullptr;
}

TestGame::~TestGame()
{
	/*delete fpsCam;
	fpsCam = nullptr;*/

	cubeShader->UnuseShader();

	glDeleteTextures(1, &texture_id);

	glDeleteBuffers(1, &ibo_cube_elements);
	glDeleteBuffers(2, buffers);
	glDeleteVertexArrays(1, &VertexArrayID);
}


/////////////////////////////////////////////////////////////////////////////////////////

//static const GLfloat g_vertex_buffer_data[] = {
//	-1.0f,-1.0f,-1.0f,
//	-1.0f,-1.0f, 1.0f,
//	-1.0f, 1.0f, 1.0f,
//	1.0f, 1.0f,-1.0f,
//	-1.0f,-1.0f,-1.0f,
//	-1.0f, 1.0f,-1.0f,
//	1.0f,-1.0f, 1.0f,
//	-1.0f,-1.0f,-1.0f,
//	1.0f,-1.0f,-1.0f,
//	1.0f, 1.0f,-1.0f,
//	1.0f,-1.0f,-1.0f,
//	-1.0f,-1.0f,-1.0f,
//	-1.0f,-1.0f,-1.0f,
//	-1.0f, 1.0f, 1.0f,
//	-1.0f, 1.0f,-1.0f,
//	1.0f,-1.0f, 1.0f,
//	-1.0f,-1.0f, 1.0f,
//	-1.0f,-1.0f,-1.0f,
//	-1.0f, 1.0f, 1.0f,
//	-1.0f,-1.0f, 1.0f,
//	1.0f,-1.0f, 1.0f,
//	1.0f, 1.0f, 1.0f,
//	1.0f,-1.0f,-1.0f,
//	1.0f, 1.0f,-1.0f,
//	1.0f,-1.0f,-1.0f,
//	1.0f, 1.0f, 1.0f,
//	1.0f,-1.0f, 1.0f,
//	1.0f, 1.0f, 1.0f,
//	1.0f, 1.0f,-1.0f,
//	-1.0f, 1.0f,-1.0f,
//	1.0f, 1.0f, 1.0f,
//	-1.0f, 1.0f,-1.0f,
//	-1.0f, 1.0f, 1.0f,
//	1.0f, 1.0f, 1.0f,
//	-1.0f, 1.0f, 1.0f,
//	1.0f,-1.0f, 1.0f
//};
//
//// One color for each vertex. They were generated randomly.
//static const GLfloat g_color_buffer_data[] = {
//	0.583f,  0.771f,  0.014f,
//	0.609f,  0.115f,  0.436f,
//	0.327f,  0.483f,  0.844f,
//	0.822f,  0.569f,  0.201f,
//	0.435f,  0.602f,  0.223f,
//	0.310f,  0.747f,  0.185f,
//	0.597f,  0.770f,  0.761f,
//	0.559f,  0.436f,  0.730f,
//	0.359f,  0.583f,  0.152f,
//	0.483f,  0.596f,  0.789f,
//	0.559f,  0.861f,  0.639f,
//	0.195f,  0.548f,  0.859f,
//	0.014f,  0.184f,  0.576f,
//	0.771f,  0.328f,  0.970f,
//	0.406f,  0.615f,  0.116f,
//	0.676f,  0.977f,  0.133f,
//	0.971f,  0.572f,  0.833f,
//	0.140f,  0.616f,  0.489f,
//	0.997f,  0.513f,  0.064f,
//	0.945f,  0.719f,  0.592f,
//	0.543f,  0.021f,  0.978f,
//	0.279f,  0.317f,  0.505f,
//	0.167f,  0.620f,  0.077f,
//	0.347f,  0.857f,  0.137f,
//	0.055f,  0.953f,  0.042f,
//	0.714f,  0.505f,  0.345f,
//	0.783f,  0.290f,  0.734f,
//	0.722f,  0.645f,  0.174f,
//	0.302f,  0.455f,  0.848f,
//	0.225f,  0.587f,  0.040f,
//	0.517f,  0.713f,  0.338f,
//	0.053f,  0.959f,  0.120f,
//	0.393f,  0.621f,  0.362f,
//	0.673f,  0.211f,  0.457f,
//	0.820f,  0.883f,  0.371f,
//	0.982f,  0.099f,  0.879f
//};

GLfloat g_vertex_buffer_data[] = {
	// front
	-1.0, -1.0,  1.0,
	1.0, -1.0,  1.0,
	1.0,  1.0,  1.0,
	-1.0,  1.0,  1.0,
	// back
	-1.0, -1.0, -1.0,
	1.0, -1.0, -1.0,
	1.0,  1.0, -1.0,
	-1.0,  1.0, -1.0,
};

GLfloat g_color_buffer_data[] = {
	// front colors
	1.0, 0.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 0.0, 1.0,
	1.0, 1.0, 1.0,
	// back colors
	1.0, 0.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 0.0, 1.0,
	1.0, 1.0, 1.0,
};

/* init_resources */
GLushort cube_elements[] = {
	// front
	0, 1, 2,
	2, 3, 0,
	// top
	1, 5, 6,
	6, 2, 1,
	// back
	7, 6, 5,
	5, 4, 7,
	// bottom
	4, 0, 3,
	3, 7, 4,
	// left
	4, 5, 1,
	1, 0, 4,
	// right
	3, 2, 6,
	6, 7, 3,
};

/////////////////////////////////////////////////////////////////////////////////////////

hBOOL TestGame::InitGame()
{
	// CREATE THE SHADERS
	cubeShader = new ShaderProgram();
	cubeShader->CompileShaders("colourShading.vert", "colourShading.frag");
	cubeShader->AddAttribute("vertexPosition");
	cubeShader->AddAttribute("vertexColor");

	cubeShader->LinkShaders();

	// Store shader in manager
	STRING name = "My Cube Shader";
	SHADER_MANAGER->StoreShaderProg(name, cubeShader);

	cubeShader->UseShader();

	textureImage = new SdlImage("res_texture.png");

	ImageManager* img = IMAGE_MANAGER;
	img->UploadImage("TestCubeTexture", textureImage);


	//glGenTextures(1, &texture_id);
	//glBindTexture(GL_TEXTURE_2D, texture_id);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexImage2D(GL_TEXTURE_2D, // target
	//	0,  // level, 0 = base, no minimap,
	//	GL_RGBA, // internalformat
	//	textureImage->GetWidth(),  // width
	//	textureImage->GetHeight(),  // height
	//	0,  // border, always 0 in OpenGL ES
	//	GL_RGBA,  // format
	//	GL_UNSIGNED_BYTE, // type
	//	textureImage->GetImageSurface()->pixels);
	//SDL_FreeSurface(textureImage->GetImageSurface());


	//glGenBuffers(1, &ibo_cube_elements);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);

	// Create Vertex Array
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	///* init_resources */
	//GLfloat cube_texcoords[] = {
	//	// front
	//	0.0, 0.0,
	//	1.0, 0.0,
	//	1.0, 1.0,
	//	0.0, 1.0,
	//};
	//glGenBuffers(1, &vbo_cube_texcoords);
	//glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_texcoords);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(cube_texcoords), cube_texcoords, GL_STATIC_DRAW);
	///* render */
	//glEnableVertexAttribArray(3);
	//glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_texcoords);
	//glVertexAttribPointer(
	//	0, // attribute
	//	2,                  // number of elements per vertex, here (x,y)
	//	GL_FLOAT,           // the type of each element
	//	GL_FALSE,           // take our values as-is
	//	0,                  // no extra data between each position
	//	0                   // offset of first element
	//);

	// GEN buffers
	glGenBuffers(2, buffers);

	// Vertices
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// Colors
	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);



















	// Set location of uniform variables of matrices in shader
	location = glGetUniformLocation(cubeShader->GetProgramID(), "model_matrix");
	view_matrix_location = glGetUniformLocation(cubeShader->GetProgramID(), "view_matrix");
	projection_matrix_location = glGetUniformLocation(cubeShader->GetProgramID(), "projection_matrix");

	//fpsCam = new FPSCamera();
	FLY_DEBUG_CAM->SetProjLocation(projection_matrix_location);
	FLY_DEBUG_CAM->SetViewLocation(view_matrix_location);

	return true;
}

void TestGame::GameUpdate(const hFLOAT _deltaTime)
{
	// window title bar update
	STRINGSTREAM ss;
	ss << "Test Game | FPS: " << fps;
	STRING _fps = ss.str();

	SDL_SetWindowTitle(gameWindow->GetWindow(), _fps.c_str());

	//fpsCam->Update(_deltaTime);
	FLY_DEBUG_CAM->Update(_deltaTime);
}

void TestGame::GameRender()
{
	//// Draw the triangle !
	glm::mat4 Model = glm::mat4(1.0f);
	glUniformMatrix4fv(location, 1, GL_FALSE, &Model[0][0]);
	//glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12*3 indices starting at 0 -> 12 triangles

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
	hINT size;  glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
}

void TestGame::GameInput(SDL_Event & _evnt)
{
	//fpsCam->MoveCamera(_evnt);
	FLY_DEBUG_CAM->MoveCamera(_evnt);
}
